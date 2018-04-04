

#pragma once


#include <Wt/WContainerWidget>
#include <Wt/WTreeTable.h>

#include "Observable.hpp"
#include "UsersInfo.hpp"
#include "AccountsInfo.hpp"

#include <memory>

class UsersInfoWidget : public Wt::WContainerWidget, public Observer{
public:
    UsersInfoWidget ( std::shared_ptr<UsersInfo>, std::shared_ptr<AccountsInfo> ); 
    virtual ~UsersInfoWidget ();
    void update() override;

private:
    std::vector<std::string> get_accounts();
    void make_move_dialog(Wt::WDialog* dialog, 
        std::vector<std::string> account_names, 
        std::string name,
        UserInfo& user_info);

    std::shared_ptr<UsersInfo> users_info;
    std::shared_ptr<AccountsInfo> accounts_info;
};

