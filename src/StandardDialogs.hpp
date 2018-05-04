

#pragma once

#include <string>
#include <memory>
#include <Wt/WDialog.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

inline Wt::WDialog* make_modal_dialog( Wt::WWidget* widget )
{
  auto dialog  = widget->addChild(std::make_unique<Wt::WDialog>());
  dialog->finished().connect(
      [=](){
        widget->removeChild( dialog );
      }
  );

  return dialog;
}

inline void make_error_dialog( Wt::WDialog* dialog, std::string text ){
  auto con = dialog->contents()->addWidget(std::make_unique<Wt::WContainerWidget>());

  con->addWidget( std::make_unique<Wt::WText>( text ) );

  auto ok_button = con->addWidget(std::make_unique<Wt::WPushButton>( "ok" ) );
  ok_button->clicked().connect([=] {
    dialog->accept();
  });
}


// TODO needs to be made prettyer
inline void make_confirm_dialog( 
    Wt::WWidget* widget, 
    std::function<void()> on_success, 
    std::string text 
  )
{
  auto dialog = make_modal_dialog( widget );

  auto con = dialog->contents()->addWidget(std::make_unique<Wt::WContainerWidget>());

  con->addWidget( std::make_unique<Wt::WText>( text ) );

  auto ok_button = con->addWidget(std::make_unique<Wt::WPushButton>( "ok" ) );
  ok_button->clicked().connect([=] {
      on_success();
      dialog->accept();
  });

  auto cancel_button = con->addWidget(std::make_unique<Wt::WPushButton>( "cancel" ) );
  cancel_button->clicked().connect([=] {
      dialog->reject();
  });

  dialog->show();
}


