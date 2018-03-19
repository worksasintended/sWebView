
#pragma once
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WMenu.h>

#include "Observable.hpp"
#include "AuthWidget.hpp"


class RootApplication : public Wt::WApplication, public Observer{
  public:
    RootApplication(const Wt::WEnvironment& env);
    virtual ~RootApplication();

    virtual void update() override;
  private:
    AuthWidget* authWidget = nullptr;
    Wt::WMenuItem* logoutButton=nullptr;
};
