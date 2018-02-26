#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WServer.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WStackedWidget.h>
#include <string>

#include "AuthWidget.hpp"

using namespace Wt;
using namespace std;

class RootApplication : public Wt::WApplication{
  public: 
    RootApplication(const Wt::WEnvironment& env) : Wt::WApplication(env){
      
      //basic layout
      auto bootstrapTheme = make_shared<Wt::WBootstrapTheme>();
      bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
      bootstrapTheme->setResponsive(true);
      setTheme(bootstrapTheme);
      useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
      auto layout = root()->setLayout(make_unique<WBorderLayout>());
      auto container = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::North );
      auto image = container->addWidget( make_unique<Wt::WImage>(Wt::WLink("banner.png")) );
      
      //navigation bar
      Wt::WNavigationBar *navigation = container->addWidget(make_unique<Wt::WNavigationBar>());
      navigation->setResponsive(true);
      Wt::WStackedWidget *contentsStack = container->addWidget(Wt::cpp14::make_unique<Wt::WStackedWidget>());
      contentsStack->addStyleClass("contents");
      auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
      auto leftMenu_ = navigation->addMenu(std::move(leftMenu));
      leftMenu_->addItem("Information", make_unique<Wt::WText>("Information part, visible without authentification"));
      leftMenu_->addItem("Administration", make_unique<AuthWidget>());
    }

    virtual ~RootApplication() {

    }

};

std::unique_ptr<WApplication> createApplication(const Wt::WEnvironment& env){
  return make_unique<RootApplication>(env);
}

int main(int argc, char **argv){
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

