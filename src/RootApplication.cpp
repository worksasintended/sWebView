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
#include "RootApplication.hpp"
#include "UsersInfoWidget.hpp"
#include "AccountsInfoWidget.hpp"
#include "JobsInfoWidget.hpp"
#include "ReservationsInfoWidget.hpp"

using namespace Wt;
using namespace std;


RootApplication::RootApplication(const Wt::WEnvironment& env) : 
  Wt::WApplication(env)
{

      //basic layout
      auto bootstrapTheme = make_shared<Wt::WBootstrapTheme>();
      bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
      bootstrapTheme->setResponsive(true);
      setTheme(bootstrapTheme);
      useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
      auto layout = root()->setLayout(make_unique<WBorderLayout>());
      auto container = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::North );
      auto image = container->addWidget( make_unique<Wt::WImage>(Wt::WLink("banner.png")) );
      container->setOverflow( Wt::Overflow::Scroll );

      //connect to slurm and create PartitionsInfo instance
      partitions_info = make_shared<PartitionsInfo>();
      this->add_updatable( partitions_info.get() );
      //jobs_info = make_shared<JobsInfo>();

      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
      slurm_db.connect();

      //navigation bar
      auto navigation = container->addWidget(make_unique<Wt::WNavigationBar>());
      navigation->setResponsive(true);
      std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;

      auto contentsStack = container->addWidget(make_unique<Wt::WStackedWidget>());
      contentsStack->addStyleClass("contents");
      std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;

      auto leftMenu = make_unique<Wt::WMenu>(contentsStack);
      auto leftMenu_ = navigation->addMenu(std::move(leftMenu));
      auto rightMenu = make_unique<Wt::WMenu>();
      auto rightMenu_ = navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);
      std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;

      leftMenu_->addItem("Information", make_unique<InfoWidget>(partitions_info));
      
      

      // refresh button
      auto refreshButton=rightMenu_->addItem("Refresh", make_unique<Wt::WPushButton>());
      refreshButton->clicked().connect(
	      [=](){
                this->refresh();
		rightMenu_->select(-1);
	      }
      );
      //Login-logout-button
      auto authWidget_up = make_unique<AuthWidget>();
      authWidget = authWidget_up.get();
      
      //TODO not working anymore!!!
      authWidget->add_observer( this );
      leftMenu_->addItem("Administration", std::move(authWidget_up));
      logoutButton = rightMenu_->addItem("Logout", make_unique<Wt::WPushButton>());
      logoutButton->clicked().connect(
          [=](){
            authWidget->logout();
	    rightMenu_->select(-1);
          }
      );
      logoutButton->hide();
}


RootApplication::~RootApplication() {

}

//hide / show logout button
void RootApplication::update() {
  if ( authWidget->isLoggedIn() ) {
    logoutButton->show();
    this->refresh();
  }else{
    logoutButton->hide();
  }
}
//updating all data observables
void RootApplication::refresh() {
  for( auto& o : observables ){
    o->update_data();
  }
} 




void RootApplication::add_updatable(Observable* _observable) {
  observables.push_back(_observable);  
}

SlurmDB& RootApplication::get_slurm_db() {
  if ( !slurm_db.is_connected() ) {
    std::cout << "Warning: slurm_db is not connected" << std::endl;
  }
  return slurm_db;
}
