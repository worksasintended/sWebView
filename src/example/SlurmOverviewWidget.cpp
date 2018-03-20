#include "SlurmOverviewWidget.hpp"
#include "DialogUtil.hpp"
#include <Wt/WDialog.h>
#include <Wt/WPushButton.h>

using namespace std;
using namespace Wt;

SlurmOverviewWidget::SlurmOverviewWidget(SlurmOverviewData* _data) {
  data = _data;
  data->addObserver(this);
  update();
}

SlurmOverviewWidget::~SlurmOverviewWidget() {
  
}


void SlurmOverviewWidget::update(){
  this->clear();
  auto button = this->addWidget( make_unique<WPushButton>("test") );
  button->clicked().connect(
    [=](){
      auto dialog = this->addChild( make_unique<WDialog>("test dialog") );
      make_ok_cancel_dialog( dialog, "content" );
      dialog->show();
      dialog->finished().connect(
        [=](){
          this->removeChild( dialog );
        }
      );
    }
  );  

}
