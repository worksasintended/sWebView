#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WBorderLayout.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WPushButton.h>
#include <string>

#include "InfoWidget.hpp"
#include "PartitionsInfo.hpp"
#include "RootApplication.hpp"
#include "UsersInfo.hpp"
using namespace Wt;
using namespace std;


RootApplication::RootApplication(const Wt::WEnvironment& env):Wt::WApplication(env){

      //basic layout
      auto bootstrapTheme = make_shared<Wt::WBootstrapTheme>();
      bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
      bootstrapTheme->setResponsive(true);
      setTheme(bootstrapTheme);
      useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
      auto layout = root()->setLayout(make_unique<WBorderLayout>());
      auto container = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::North );
      auto image = container->addWidget( make_unique<Wt::WImage>(Wt::WLink("banner.png")) );

      auto partitions_info = make_shared<PartitionsInfo>();
      SlurmDB slurm_db;
      slurm_db.connect();
      auto users_info = make_shared<UsersInfo>(slurm_db);

      //navigation bar
      Wt::WNavigationBar *navigation = container->addWidget(make_unique<Wt::WNavigationBar>());
      navigation->setResponsive(true);
      Wt::WStackedWidget *contentsStack = container->addWidget(Wt::cpp14::make_unique<Wt::WStackedWidget>());
      contentsStack->addStyleClass("contents");
      auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
      auto leftMenu_ = navigation->addMenu(std::move(leftMenu));
      auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();
      auto rightMenu_ = navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);
      leftMenu_->addItem("Information", make_unique<InfoWidget>(partitions_info));

      // refresh button
      auto refreshButton=rightMenu_->addItem("Refresh", make_unique<Wt::WPushButton>());
      refreshButton->clicked().connect(
	      [=](){
	         partitions_info->update_data();
                 users_info->update_data();
	      }
      );
      //Login-logout-button
      auto authWidget_up = make_unique<AuthWidget>();
      authWidget = authWidget_up.get();
      
      authWidget->add_observer( this );
      leftMenu_->addItem("Administration", std::move(authWidget_up));
      logoutButton = rightMenu_->addItem("Logout", make_unique<Wt::WPushButton>());
      logoutButton->clicked().connect(
          [=](){
            authWidget->logout();
          }
      );
      logoutButton->hide();
}


RootApplication::~RootApplication() {

}


void RootApplication::update() {
  if ( authWidget->isLoggedIn() ) {
    logoutButton->show();
  }else{
    logoutButton->hide();
  }
}
