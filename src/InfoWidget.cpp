#include <Wt/WText.h>
#include "InfoWidget.hpp"
using namespace std;

InfoWidget::InfoWidget(){
  this->addWidget(make_unique<Wt::WText>("This is the information widget", Wt::TextFormat::Plain));
}


InfoWidget::~InfoWidget() {

}

