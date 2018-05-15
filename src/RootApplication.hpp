
#pragma once
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WMenu.h>

#include "Observable.hpp"
#include "AuthWidget.hpp"
#include "PartitionsInfo.hpp"
#include "UsersInfo.hpp"
#include "AccountsInfo.hpp"
#include "ClustersInfo.hpp"
#include "JobsInfo.hpp"
#include "ReservationsInfo.hpp"
#include "SlurmDB.hpp"


class RootApplication : public Wt::WApplication, public Observer{
  public:
    RootApplication(const Wt::WEnvironment& env);
    virtual ~RootApplication();

    virtual void update() override;

    void refresh();
  
    void add_updatable(Observable*);

    SlurmDB& get_slurm_db();

  private:
    AuthWidget* authWidget = nullptr;
    Wt::WMenuItem* logoutButton=nullptr;
    std::shared_ptr<PartitionsInfo> partitions_info;
    std::vector<Observable*> observables;
  
//    std::shared_ptr<UsersInfo> users_info;
//    std::shared_ptr<AccountsInfo> accounts_info;
//    std::shared_ptr<ClustersInfo> clusters_info;
//    std::shared_ptr<JobsInfo> jobs_info;
//    std::shared_ptr<ReservationsInfo> reservations_info;
    SlurmDB slurm_db;
};
