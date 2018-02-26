#include <string>

#include "AuthWidget.hpp"
#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

using namespace std;

AuthWidget::AuthWidget() :
  session_("app/"s + "auth.db")
{
  auto authWidget = this->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );
  authWidget->model()->addPasswordAuth(&Session::passwordAuth());
  //change to true to enable registration
  authWidget->setRegistrationEnabled(false);
  authWidget->processEnvironment();
}


AuthWidget::~AuthWidget() {
  
}
