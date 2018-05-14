#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include "InfoWidget.hpp"

using namespace std;
using namespace Wt;


InfoWidget::InfoWidget( std::shared_ptr<PartitionsInfo> _pinfo ){

  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  // first create something we can track with the update function
  partitions_info = _pinfo;
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  partitions_info->add_observer(this);
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  partitions_info->update_data();
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;

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
