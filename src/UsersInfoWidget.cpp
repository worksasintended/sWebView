

#include "UsersInfoWidget.hpp"
#include <Wt/WTreeTable.h>
#include <Wt/WTreeTableNode.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>

#include "StandardDialogs.hpp"

using namespace std;
using namespace Wt;

UsersInfoWidget::UsersInfoWidget ( std::shared_ptr<UsersInfo> _users_info,
                                   std::shared_ptr<AccountsInfo> _accounts_info ){
  users_info = _users_info;
  accounts_info = _accounts_info;
  users_info->add_observer(this);
  accounts_info->add_observer(this);

  this->update();
}

UsersInfoWidget::~UsersInfoWidget()  {

}

void UsersInfoWidget::make_move_dialog(
    WDialog* dialog, 
    std::vector<std::string> account_names, 
    UserInfo& user_info 
){
  auto con = dialog->contents()->addWidget(make_unique<WContainerWidget>());

  auto cb = con->addWidget(make_unique<Wt::WComboBox>());

  for( auto& account_name : account_names ){
     cb->addItem( account_name );
  }

  auto cancel_button = con->addWidget(make_unique<WPushButton>( "cancel" ) );
  cancel_button->clicked().connect([=] {
    dialog->reject();
  });
  auto ok_button = con->addWidget(make_unique<WPushButton>( "ok" ) );
  ok_button->clicked().connect([=] {
    try{
      users_info->set_default_account( user_info, cb->valueText().toUTF8() );
    }catch ( std::invalid_argument& ia ) {
      auto edialog = this->addChild(
          make_unique<Wt::WDialog>("Error")
      );
      make_error_dialog( edialog, ia.what() );
      edialog->show();
      edialog->finished().connect(
        [=](){
          this->removeChild( edialog );
          dialog->accept();
        }
      );
    }
    dialog->accept();
  });
}

void UsersInfoWidget::make_add_dialog(
    WDialog* dialog, 
    std::vector<std::string> account_names, 
    UserInfo user_info 
){
  auto con = dialog->contents()->addWidget(make_unique<WContainerWidget>());

  auto cb = con->addWidget(make_unique<Wt::WComboBox>());

  for( auto& account_name : account_names ){
     cb->addItem( account_name );
  }

  auto cancel_button = con->addWidget(make_unique<WPushButton>( "cancel" ) );
  cancel_button->clicked().connect([=](){
    dialog->reject();
  });
  auto ok_button = con->addWidget(make_unique<WPushButton>( "ok" ) );
  ok_button->clicked().connect([=](){
#if 1
    try{
      users_info->add_to_account( user_info, cb->valueText().toUTF8() );
    }catch ( std::invalid_argument& ia ) {
      auto edialog = this->addChild(
          make_unique<Wt::WDialog>("Error")
      );
      make_error_dialog( edialog, ia.what() );
      edialog->show();
      edialog->finished().connect(
        [=](){
          this->removeChild( edialog );
          dialog->accept();
        }
      );
    }
    dialog->accept();
#endif
  });
}

void UsersInfoWidget::update(){
  std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;
  this->clear();

  // TODO someone has to change the style of this table 
  // buttons made of icons or something like this
  auto tree_table = this->addWidget( make_unique<WTreeTable>() );
  tree_table->setTreeRoot( make_unique<WTreeTableNode>("root"), "Accounts" );
  auto root = tree_table->treeRoot();

  std::map<std::string, WTreeTableNode*> accounts;

  // first create the accounts in the table
  for( auto& account_info : *accounts_info ){
    int ctr = 1;
    auto node = make_unique<WTreeTableNode>(account_info.get_name()); 
    node->setColumnWidget( ctr++ , make_unique<WText>(to_string(account_info.get_fairshare())) );
    accounts.emplace( account_info.get_name(), node.get() );
    root->addChildNode(std::move(node));
  }
  
  // second add the users to their accounts
  for( auto& user_info : *users_info ){
    for( auto& user_account : user_info.get_account_names() ) {
      WTreeTableNode* account = nullptr;
      auto search = accounts.find(user_account);
      if(search != accounts.end()) {
          account = search->second;
      } else {
          continue;
      }

      auto node = make_unique<WTreeTableNode>(user_info.get_name()); 
      auto user = node.get();
      account->addChildNode( std::move(node) );  
      int ctr = 1;

      {
        auto button = make_unique<WPushButton>("add");
        auto add_button = button.get();
        user->setColumnWidget( ctr++ , std::move(button) );
        add_button->clicked().connect(
          [=](){
            auto dialog = this->addChild(
                make_unique<Wt::WDialog>("Add "s + user_info.get_name() + " to account")
            );
            make_add_dialog( 
                dialog, 
                accounts_info->get_account_names(), 
                user_info
            );
            dialog->show();
            dialog->finished().connect(
              [=](){
                this->removeChild( dialog );
              }
            );
          }
        );
      }

      {
        auto button = make_unique<WPushButton>("default");
        auto move_button = button.get();
        user->setColumnWidget( ctr++ , std::move(button) );
        move_button->clicked().connect(
          [=,&user_info](){
            auto dialog = this->addChild(
                make_unique<Wt::WDialog>("Set "s + user_info.get_name() + " default account")
            );
            make_move_dialog( 
                dialog, 
                user_info.get_account_names(), 
                user_info
            );
            dialog->show();
            dialog->finished().connect(
              [=](){
                this->removeChild( dialog );
              }
            );
          }
        );
      }

    }

  }

  root->expand();
  
  std::cout << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << std::endl;

}
