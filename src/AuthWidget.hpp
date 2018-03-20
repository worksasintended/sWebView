
#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "RootApplication.hpp"
#include "model/Session.h"

#include "Observable.hpp"

using namespace std;
using namespace Wt;

class AuthWidget : public Wt::WContainerWidget, public Observable{
public:
    AuthWidget (); 
    virtual ~AuthWidget ();
    void logout();
    Wt::WContainerWidget* adminPanel;
    bool isLoggedIn();
private:
  void authEvent();
  Wt::Auth::AuthWidget* authWidget=nullptr;
  Session session_;
};
