#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include "InfoWidget.hpp"

using namespace std;
using namespace Wt;


InfoWidget::InfoWidget(){

  // first create something we can track with the update function
  partitions_info = new PartitionsInfo();
  partitions_info->add_observer(this);
  partitions_info->update_data();

  // call the routine that draws all elements to this widget
  update();
}


InfoWidget::~InfoWidget() {

}

void InfoWidget::update(){
  this->clear();
  this->addWidget(make_unique<Wt::WText>("This is the information widget", Wt::TextFormat::Plain));

  auto update = this->addWidget(make_unique<WPushButton>("update") );
  update->clicked().connect(
    [=](){
      partitions_info->update_data();
    }
  );

  for ( auto& part : *partitions_info){
    this->addWidget( make_unique<WText>(part.get_name() ) );
  }

}
