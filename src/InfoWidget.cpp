#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include "InfoWidget.hpp"

using namespace std;
using namespace Wt;


InfoWidget::InfoWidget( std::shared_ptr<PartitionsInfo> _pinfo ){

  // first create something we can track with the update function
  partitions_info = _pinfo;
  partitions_info->add_observer(this);
  partitions_info->update_data();

  // call the routine that draws all elements to this widget
  update();
}


InfoWidget::~InfoWidget() {

}

void InfoWidget::update(){
  this->clear();

  for ( auto& part : *partitions_info){
    this->addWidget( make_unique<WText>(part.get_name() ) );
  }

}
