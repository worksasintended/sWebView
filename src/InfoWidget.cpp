#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <slurm/slurm.h>
#include "InfoWidget.hpp"

using namespace std;
using namespace Wt;

InfoWidget::InfoWidget(){
  this->addWidget(make_unique<Wt::WText>("This is the information widget", Wt::TextFormat::Plain));
  auto update = this->addWidget(make_unique<WPushButton>("update") );
  update->clicked().connect(
    [=](){
      partition_info_msg_t* info;

      time_t now = time(NULL);
      now = now - (60 * 60 * 24);

      slurm_load_partitions(now, &info, SHOW_FEDERATION);
      slurm_print_partition_info_msg( stdout, info, 0 );
    }
  );
}


InfoWidget::~InfoWidget() {

}

