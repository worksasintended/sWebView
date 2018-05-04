


#include "AccountsInfoWidget.hpp"
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>

#include "StandardDialogs.hpp"

using namespace std;
using namespace Wt;

AccountsInfoWidget::AccountsInfoWidget (
    std::shared_ptr<AccountsInfo> _accounts_info,
    std::shared_ptr<ClustersInfo> _clusters_info
    ){
  accounts_info = _accounts_info;
  clusters_info = _clusters_info;
  accounts_info->add_observer(this);
  clusters_info->add_observer(this);

  this->update();
}

AccountsInfoWidget::~AccountsInfoWidget()  {

}


void AccountsInfoWidget::make_add_dialog( WDialog* dialog ){

  dialog->setWindowTitle( "Add Account" );
  auto con = dialog->contents()->addWidget(make_unique<WContainerWidget>());

  auto name_le = con->addWidget( make_unique<WLineEdit>("") );
  auto description_le = con->addWidget( make_unique<WLineEdit>("") );
  auto cluster_cb = con->addWidget( make_unique<WComboBox>() );

  for( auto& cluster_info : *clusters_info ){
    cluster_cb->addItem( cluster_info.get_name() );
  }

  auto cancel_button = con->addWidget(make_unique<WPushButton>( "cancel" ) );
  cancel_button->clicked().connect([=] {
    dialog->reject();
  });
  auto ok_button = con->addWidget(make_unique<WPushButton>( "ok" ) );
  ok_button->clicked().connect([=] {
    if ( name_le->text() != "" && description_le->text() != "" ) {
      try{
      accounts_info->create_account(
          name_le->text().toUTF8(), 
          description_le->text().toUTF8(),
          "linux"
      );
      }catch( std::string& e ) {
        auto error_dialog = make_modal_dialog( dialog->parent() ); 
        make_error_dialog( error_dialog, e );
        error_dialog->show();
      }
    }
    dialog->accept();
  });
}

void AccountsInfoWidget::update(){
  this->clear();

  auto add_button =  this->addWidget( make_unique<WPushButton>("+") );

  add_button->clicked().connect(
    [=](){
      auto dialog = make_modal_dialog(this);
      make_add_dialog( dialog );
      try{
	dialog->show();
      }catch( std::exception& e ) {
	e.what();
      }
    }
  );

  auto table = this->addWidget( make_unique<WTable>() );

  // optical stuff
  table->setHeaderCount(1);
  table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");

  int column_ctr = 0;
  int line_ctr = 0;
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("account_name"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("faishare"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("operations"));
  line_ctr++;

  for( auto& account_info : *accounts_info ){
    column_ctr = 0 ;
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( account_info.get_name() ) ); 
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( to_string(account_info.get_fairshare()) ) ); 

    auto delete_button = table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WPushButton>( "-" ) ); 
    delete_button->clicked().connect(
      [=](){
        make_confirm_dialog(
          this,
          [=]() {
            accounts_info->delete_account(account_info);
          },
          "Do you really want to delete the account?"
          );
      }
    );

    line_ctr++;
  }

}














