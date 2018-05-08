#pragma once
#include <Wt/WContainerWidget.h>
#include "UsersInfo.hpp"
#include "AccountsInfo.hpp"
#include "ClustersInfo.hpp"
#include "JobsInfo.hpp"
#include "ReservationsInfo.hpp"



class AdminWidget : public Wt::WContainerWidget {
public:
    AdminWidget ();
    virtual ~AdminWidget ();
private:
    std::shared_ptr<UsersInfo> users_info;
    std::shared_ptr<AccountsInfo> accounts_info;
    std::shared_ptr<ClustersInfo> clusters_info;
    std::shared_ptr<JobsInfo> jobs_info;
    std::shared_ptr<ReservationsInfo> reservations_info;
};
