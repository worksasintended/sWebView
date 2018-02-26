
#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/Auth/AuthModel.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "RootApplication.hpp"
#include "model/Session.h"

using namespace std;
using namespace Wt;

class AuthWidget : public Wt::WContainerWidget{
public:
    AuthWidget (); 
    virtual ~AuthWidget ();
    void logout();
    Wt::WContainerWidget* adminPanel;
private:
  void authEvent();
  Wt::Auth::AuthWidget* authWidget=nullptr;
  Session session_;
};
