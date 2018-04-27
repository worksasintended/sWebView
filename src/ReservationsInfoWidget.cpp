

#include "ReservationsInfoWidget.hpp"
#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>

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

  // TODO someone has to change the style of this table 
  // buttons made of icons or something like this
  auto table = this->addWidget( make_unique<WTable>() );
  table->setHeaderCount(1);
  table->setWidth(WLength("100%"));

  auto counter = 0;
  for (auto& reservation: *reservations_info){
    cout << "test" << endl;
    auto reservationname = reservation.get_name();
    table->elementAt(counter, 0)->addWidget(make_unique<WText>(reservationname));
  }

}
