
#pragma once
#include <Wt/WApplication.h>
#include <Wt/WPushButton.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WMenu.h>



class RootApplication : public Wt::WApplication{
  public:
    RootApplication(const Wt::WEnvironment& env);
    virtual ~RootApplication();

    void hideLogoutButton();
    void showLogoutButton();

    Wt::WMenuItem* logoutButton=nullptr;
};
