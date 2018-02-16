/*
 * Copyright (C) 2010 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WServer>
#include <Wt/WBootstrapTheme>

#include <Wt/Auth/AuthModel>
#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>
#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WBorderLayout>
#include <Wt/WTimer>
#include <Wt/WPushButton>
#include <Wt/WImage>
#include <Wt/Dbo/Dbo.h>

#include "model/Session.h"
#include "SlurmOverviewWidget.hpp"
#include <Wt/Dbo/backend/Sqlite3.h>

#include <string>

using namespace Wt;
using namespace std;

class AuthApplication : public Wt::WApplication
{
public:
  AuthApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
      session_(appRoot() + "auth.db")
  {
    // call authEvent of this if login state changes
    session_.login().changed().connect(this, &AuthApplication::authEvent);

    // basic wt setup 
    auto bootstrapTheme = make_shared<Wt::WBootstrapTheme>();
    bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
    bootstrapTheme->setResponsive(true);
    setTheme(bootstrapTheme);
    useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");

    messageResourceBundle().use(appRoot() + "text");

    // fill app with widgets
    
    auto layout = root()->setLayout(make_unique<WBorderLayout>());
    auto container = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::North );

    auto image = container->addWidget( make_unique<Wt::WImage>(Wt::WLink("banner.png")) );
    auto authWidget = container->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );

    authWidget->model()->addPasswordAuth(&Session::passwordAuth());
    authWidget->setRegistrationEnabled(true);

    auto sovd = make_unique<SlurmOverviewData>();
    logged_in_content = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::Center );
    logged_in_content->addWidget( make_unique<SlurmOverviewWidget>(sovd.get()) );
    logged_in_content->hide();
    logged_in_content->setOverflow( Wt::Overflow::Scroll );

    sovd->notifyObservers();
    
    authWidget->processEnvironment();
  }

  WContainerWidget* logged_in_content = nullptr;

  void authEvent() {
    if (session_.login().loggedIn()) {
      logged_in_content->show();
    }else{
      logged_in_content->hide();
    }
  }

private:
  Session session_;
};

std::unique_ptr<WApplication> createApplication(const Wt::WEnvironment& env)
{
  return make_unique<AuthApplication>(env);
}

int main(int argc, char **argv)
{
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

    Session::configureAuth();

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
