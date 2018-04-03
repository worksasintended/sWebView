

#include "UsersInfoWidget.hpp"
#include <Wt/WTreeTable.h>
#include <Wt/WTreeTableNode.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>

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

void UsersInfoWidget::make_move_dialog(WDialog* dialog, std::string name ){
  
}

void UsersInfoWidget::update(){
  this->clear();

  auto tree_table = this->addWidget( make_unique<WTreeTable>() );
  tree_table->setTreeRoot( make_unique<WTreeTableNode>("root"), "Accounts" );
  auto root = tree_table->treeRoot();

  // display them in raw format
  for( auto& user_info : *users_info ){
    auto node = make_unique<WTreeTableNode>(user_info.get_name()); 
    auto user = node.get();
    root->addChildNode( std::move(node) );  
    int ctr = 1;
    auto button = make_unique<WPushButton>("move");
    auto move_button = button.get();
    user->setColumnWidget( ctr++ , std::move(button) );
    move_button->clicked().connect(
      [=,&user_info](){
        auto dialog = this->addChild(
            make_unique<Wt::WDialog>("Move "s + user_info.get_name() + " to group")
        );
        // TODO continue to implement the dialog here
#if 0
        make_move_dialog( dialog, &this->groups, user_info.get_name() );
        dialog->show();
        dialog->finished().connect(
          [=](){
            this->update();
            this->removeChild( dialog );
          }
        );
#endif
      }
    );

  }
  

}
