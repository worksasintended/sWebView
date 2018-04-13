
#pragma once


#include <Wt/WContainerWidget>
#include <Wt/WTreeTable.h>

#include "Observable.hpp"
#include "AccountsInfo.hpp"
#include "ClustersInfo.hpp"

#include <memory>

class AccountsInfoWidget : public Wt::WContainerWidget, public Observer{
public:
    AccountsInfoWidget ( std::shared_ptr<AccountsInfo>, std::shared_ptr<ClustersInfo> ); 
    virtual ~AccountsInfoWidget ();
    void update() override;

private:
    
    void make_add_dialog(Wt::WDialog* dialog);

    std::shared_ptr<AccountsInfo> accounts_info;
    std::shared_ptr<ClustersInfo> clusters_info;
};

