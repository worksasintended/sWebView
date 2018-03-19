#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include "InfoWidget.hpp"

using namespace std;
using namespace Wt;


InfoWidget::InfoWidget(){

  // first create something we can track with the update function
  partitions_info_data = new PartitionsInfoData();
  partitions_info_data->add_observer(this);
  partitions_info_data->update_data();

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
      partitions_info_data->update_data();
    }
  );

  // now add some elements that display the information from the infered slurm data
  for (int i = 0; i < partitions_info_data->number_of_partitions(); ++i){
    this->addWidget( make_unique<WText>(partitions_info_data->get_partition_name(i) ) );
  }

}
