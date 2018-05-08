#include <Wt/WMenu.h>
#include <Wt/WTextArea>
#include <Wt/WText.h>
#include "AdminWidget.hpp"
#include "RootApplication.hpp"
#include "UsersInfoWidget.hpp"
#include "AccountsInfoWidget.hpp"
#include "JobsInfoWidget.hpp"
#include "ReservationsInfoWidget.hpp"

#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>

using namespace std;
using namespace Wt;

AdminWidget::AdminWidget(){

  auto instance = WApplication::instance();
  auto root_app = (RootApplication*)instance;  auto slurm_db = root_app->get_slurm_db();

  users_info = make_shared<UsersInfo>(slurm_db);
  accounts_info = make_shared<AccountsInfo>(slurm_db);
  clusters_info = make_shared<ClustersInfo>(slurm_db);
  reservations_info = make_shared<ReservationsInfo>();

  Wt::WStackedWidget *contentsStack = this->addWidget( make_unique<Wt::WStackedWidget>());
  // add menu to the left
  Wt::WMenu *menu = this->addWidget(make_unique<Wt::WMenu>(contentsStack));
  menu->setStyleClass("nav nav-pills nav-stacked");
  menu->setWidth(150);

  
  menu->addItem("User Management", make_unique<UsersInfoWidget>(users_info,accounts_info));
#if 0
  menu->addItem("Account Management", make_unique<AccountsInfoWidget>(accounts_info, clusters_info));
  menu->addItem("Job Management", make_unique<JobsInfoWidget>(jobs_info));
  menu->addItem("Reservation Management", make_unique<ReservationsInfoWidget>(reservations_info));
#endif
  std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
}


AdminWidget::~AdminWidget() {

}
 
