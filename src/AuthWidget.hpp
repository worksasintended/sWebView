
#pragma once
#include <Wt/WContainerWidget.h>

#include "model/Session.h"

class AuthWidget : public Wt::WContainerWidget {
public:
    AuthWidget (); 
    virtual ~AuthWidget ();

private:
  Session session_;
};
