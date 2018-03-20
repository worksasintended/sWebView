#include <Wt/WText.h>
#include "AdminWidget.hpp"
using namespace std;

AdminWidget::AdminWidget(){
  this->addWidget(make_unique<Wt::WText>("This is the administration widget", Wt::TextFormat::Plain));
}


AdminWidget::~AdminWidget() {

}
 
