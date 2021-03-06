

#include "ReservationsInfoWidget.hpp"
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>
#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <regex>

#include "StandardDialogs.hpp"

using namespace std;
using namespace Wt;

ReservationsInfoWidget::ReservationsInfoWidget ( std::shared_ptr<ReservationsInfo> _reservations_info ){
  reservations_info = _reservations_info;
  reservations_info->add_observer(this);

  this->update();
}

ReservationsInfoWidget::~ReservationsInfoWidget()  {

}


void ReservationsInfoWidget::update(){
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

  auto result = this->addWidget(make_unique<Wt::WTemplate>(Wt::WString::tr("customForm-template")));

  auto search_field = make_unique<WLineEdit>( search_regex_string );
  auto search_field_ptr = search_field.get();
  search_field->changed().connect( [=](){
      this->search_regex_string = search_field_ptr->text().toUTF8();
      this->update();    
    }
  );

  result->bindWidget("name", std::move(search_field) );

  auto button = make_unique<WPushButton>("search");

  result->bindWidget("button", std::move(button) );

  // TODO someone has to change the style of this table 
  // buttons made of icons or something like this
  auto table = this->addWidget( make_unique<WTable>() );
  table->setHeaderCount(1);
  table->setWidth(WLength("100%"));
  table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");
  table->elementAt(0, 0)->addWidget(cpp14::make_unique<WText>("Name"));
  table->elementAt(0, 1)->addWidget(cpp14::make_unique<WText>("Begin"));
  table->elementAt(0, 2)->addWidget(cpp14::make_unique<WText>("End"));
  table->elementAt(0, 3)->addWidget(cpp14::make_unique<WText>("Users"));
  regex search_regex (search_regex_string);
  int counter = 1;
  for (auto& reservation: *reservations_info){
    if  ( this->search_regex_string != "") {
      bool matchesregex = std::regex_search(reservation.get_name(), search_regex);
      if (!matchesregex) continue;
    }
    auto starttime = reservation.get_start_time_string();
    auto endtime = reservation.get_end_time_string();
    auto users = reservation.get_users();
    auto reservationname = reservation.get_name();
    table->elementAt(counter, 0)->addWidget(make_unique<WText>(reservationname));
    table->elementAt(counter, 1)->addWidget(make_unique<WText>(starttime));
    table->elementAt(counter, 2)->addWidget(make_unique<WText>(endtime));
    table->elementAt(counter, 3)->addWidget(make_unique<WText>(users));
    counter++;

  }
  

}
void ReservationsInfoWidget::make_add_dialog (WDialog* dialog){

    dialog->setWindowTitle( "Add Reservation");
    auto con = dialog->contents()->addWidget(make_unique<WContainerWidget>());
    auto numberOfHours = con->addWidget( make_unique<WLineEdit>(""));
    auto cancel_button = con->addWidget(make_unique<WPushButton>( "cancel" ) );
    cancel_button->clicked().connect([=] {
     dialog->reject();
    });
    auto ok_button = con->addWidget(make_unique<WPushButton>( "ok" ) );
    ok_button->clicked().connect([=] {
     if ( numberOfHours->text() != "") {
      try{
        Wt::WString wthourstring = numberOfHours->text();
        std::string stdhourstring = wthourstring.toUTF8();
        int hourint = std::stoi(stdhourstring);
        reservations_info->create_reservation(hourint);
      }catch( std::string& e ) {
        auto error_dialog = make_modal_dialog( dialog->parent() ); 
        make_error_dialog( error_dialog, e );
        error_dialog->show();
      }
    }
    dialog->accept();
  });

  }