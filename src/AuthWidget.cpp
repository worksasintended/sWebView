#include <string>

#include "AuthWidget.hpp"
#include <Wt/Auth/AuthModel>
#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>

using namespace std;

AuthWidget::AuthWidget() :
  session_("app/"s + "auth.db")
{
  auto authWidget = this->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );
  authWidget->model()->addPasswordAuth(&Session::passwordAuth());
  authWidget->setRegistrationEnabled(true);

  authWidget->processEnvironment();
}


AuthWidget::~AuthWidget() {
  
}
