

#include "UsersInfoWidget.hpp"
#include <Wt/WTreeTable.h>
#include <Wt/WTreeTableNode.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>

using namespace std;
using namespace Wt;

UsersInfoWidget::UsersInfoWidget ( std::shared_ptr<UsersInfo> _users_info,
                                   std::shared_ptr<AccountsInfo> _accounts_info ){
  users_info = _users_info;
  accounts_info = _accounts_info;
  users_info->add_observer(this);

  this->update();
}

UsersInfoWidget::~UsersInfoWidget()  {

}

std::vector<std::string> UsersInfoWidget::get_accounts(){
  
}

void UsersInfoWidget::make_move_dialog(WDialog* dialog, std::vector<std::string> account_names, std::string name, UserInfo& user_info ){
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
    users_info->set_default_account( user_info, cb->valueText().toUTF8() );
    dialog->accept();
  });
}

void UsersInfoWidget::update(){
  this->clear();

  auto tree_table = this->addWidget( make_unique<WTreeTable>() );
  tree_table->setTreeRoot( make_unique<WTreeTableNode>("root"), "Accounts" );
  auto root = tree_table->treeRoot();

  // display them in raw format
  for( auto& user_info : *users_info ){
    std::cout << "adding user item " << std::endl;
    auto node = make_unique<WTreeTableNode>(user_info.get_name()); 
    std::cout << "done adding user item " << std::endl;
    auto user = node.get();
    root->addChildNode( std::move(node) );  
    int ctr = 1;
    auto button = make_unique<WPushButton>("move");
    auto move_button = button.get();
    user->setColumnWidget( ctr++ , std::move(button) );
#if 0
    move_button->clicked().connect(
      [=,&user_info](){
        auto dialog = this->addChild(
            make_unique<Wt::WDialog>("Move "s + user_info.get_name() + " to group")
        );
        make_move_dialog( 
            dialog, 
            accounts_info->get_account_names(), 
            user_info.get_name(), 
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
#endif

  }
  

}
