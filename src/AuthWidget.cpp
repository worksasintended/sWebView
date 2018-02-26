#include <string>

#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "RootApplication.hpp"
#include "AuthWidget.hpp"

using namespace std;

AuthWidget::AuthWidget() :
  session_("app/"s + "auth.db")
{
  authWidget = this->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );
  authWidget->model()->addPasswordAuth(&Session::passwordAuth());
  //change to true to enable registration
  authWidget->setRegistrationEnabled(false);
  authWidget->processEnvironment();


  session_.login().changed().connect(this, &AuthWidget::authEvent);

}

AuthWidget::~AuthWidget() {
  
}

void AuthWidget::authEvent(){
    if (session_.login().loggedIn()) {
      //this->showLogoutButton();
    }
    else{
      //RootApplication::hideLogoutButton();
    }
}

void AuthWidget::logout(){
  session_.login().logout();
}
