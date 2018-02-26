#include <string>

#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WBorderLayout.h>

#include "RootApplication.hpp"
#include "AuthWidget.hpp"
#include "AdminWidget.hpp"

using namespace std;
using namespace Wt;

AuthWidget::AuthWidget() :
  session_("app/"s + "auth.db")
{
  authWidget = this->addWidget( make_unique<Wt::Auth::AuthWidget>(Session::auth(), session_.users(), session_.login()) );
  authWidget->model()->addPasswordAuth(&Session::passwordAuth());
  //change to true to enable registration
  authWidget->setRegistrationEnabled(false);
  authWidget->processEnvironment();

  session_.login().changed().connect(this, &AuthWidget::authEvent);

  adminPanel = this->addWidget( make_unique<AdminWidget>());
  adminPanel->hide();


}

AuthWidget::~AuthWidget() {
  
}


void AuthWidget::authEvent(){
    if (session_.login().loggedIn()) {
      AuthWidget::adminPanel->show();
      AuthWidget::authWidget->hide();
    }
    else{
      AuthWidget::adminPanel->hide();
      AuthWidget::authWidget->show();
    }
}

void AuthWidget::logout(){
  session_.login().logout();
}
