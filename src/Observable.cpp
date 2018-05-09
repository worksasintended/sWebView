#include "Observable.hpp"
#include "RootApplication.hpp"
#include <Wt/WApplication.h>

using namespace Wt;

Observable::Observable(){
  auto instance = WApplication::instance();
  auto root_app = (RootApplication*)instance;
  root_app->add_updatable(this); 
}
void Observable::update_data() {
   throw "dont call this method";  
}
