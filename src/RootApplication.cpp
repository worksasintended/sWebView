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


      partitions_info = make_shared<PartitionsInfo>();
//      jobs_info = make_shared<JobsInfo>();

      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
      slurm_db.connect();
      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
//    users_info = make_shared<UsersInfo>(slurm_db);
//   accounts_info = make_shared<AccountsInfo>(slurm_db);
//      clusters_info = make_shared<ClustersInfo>(slurm_db);
//      reservations_info = make_shared<ReservationsInfo>();

      container->setOverflow( Wt::Overflow::Scroll );

      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
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
//      leftMenu_->addItem("User Management", make_unique<UsersInfoWidget>(users_info,accounts_info));
//      leftMenu_->addItem("Account Management", make_unique<AccountsInfoWidget>(accounts_info, clusters_info));
//      leftMenu_->addItem("Job Management", make_unique<JobsInfoWidget>(jobs_info));
//      leftMenu_->addItem("Reservation Management", make_unique<ReservationsInfoWidget>(reservations_info));

      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
      // refresh button
      auto refreshButton=rightMenu_->addItem("Refresh", make_unique<Wt::WPushButton>());
      refreshButton->clicked().connect(
	      [=](){
                this->update_data();
		rightMenu_->select(-1);
	      }
      );
      //Login-logout-button
      auto authWidget_up = make_unique<AuthWidget>();
      authWidget = authWidget_up.get();
      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
      
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
      std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;

      // run data update at startup
      //update_data();
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
//TODO: FIX ME!!
void RootApplication::update_data() {
  for( auto& o : observables ){
    std::cout << "calling" << std::endl;
    o->update_data();
  }
  
//  partitions_info->update_data();
//  accounts_info->update_data();
//  users_info->update_data(); 
//  clusters_info->update_data(); 
//  jobs_info->update_data();
//  reservations_info->update_data();
}

void RootApplication::add_updatable(Observable* _observable) {
  observables.push_back(_observable);  
}

SlurmDB& RootApplication::get_slurm_db() {
  return slurm_db;
}
