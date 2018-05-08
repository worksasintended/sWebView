#include <string>

#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBorderLayout.h>

#include "RootApplication.hpp"
#include "AuthWidget.hpp"
#include "AdminWidget.hpp"

#include "Observable.hpp"

using namespace std;
using namespace Wt;

AuthWidget::AuthWidget() :
  session_("app/"s + "auth.db")
{
  authWidget = this->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );
  authWidget->model()->addPasswordAuth(&Session::passwordAuth());
  

#if ENABLE_REGISTRATION
  authWidget->setRegistrationEnabled(true);
#else
  authWidget->setRegistrationEnabled(false);
#endif


  authWidget->processEnvironment();

  session_.login().changed().connect(this, &AuthWidget::authEvent);

  adminPanel = this->addWidget( make_unique<AdminWidget>());
  adminPanel->hide();
#if USE_DEBUG_BUILD  
  session_.login().changed().emit();
#endif
}

AuthWidget::~AuthWidget() {
  
}


void AuthWidget::authEvent(){
#if USE_DEBUG_BUILD
  if (true) {
#else
  if (session_.login().loggedIn()) {
#endif
    AuthWidget::adminPanel->show();
    AuthWidget::authWidget->hide();
  }
  else{
    AuthWidget::adminPanel->hide();
    AuthWidget::authWidget->show();
  }
  this->notify_observers();
}

void AuthWidget::logout(){
  session_.login().logout();
}

bool AuthWidget::isLoggedIn() {
  return session_.login().loggedIn();
}

void AuthWidget::update_data() {
  
}
