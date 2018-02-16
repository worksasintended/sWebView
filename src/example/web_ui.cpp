/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */


#include "web_ui.h"
#include <Wt/WLabel>
#include <Wt/WBootstrapTheme>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WValidator>
#include <Wt/WMenu>
#include <Wt/WStackedWidget>
#include <Wt/WTextArea>
#include <Wt/WBorderLayout>
#include <Wt/WImage>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WColor>
#include <Wt/WContainerWidget>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WIntValidator>
#include <Wt/WDoubleValidator>
#include <Wt/WLineEdit>
#include <Wt/WTemplate>
#include <Wt/WApplication>
#include <Wt/WServer>
#include <iostream>
#include <sstream>

//#include "ImagesWidget.h"

using namespace Wt;
using namespace std;
// c++0x only, for std::bind
// #include <functional>

class WebUIApplication : public WApplication
{
public:
  WebUIApplication(const WEnvironment& env);

private:
};

WebUIApplication::WebUIApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Remote Visualization UI");                               // application title
  Wt::WBootstrapTheme *bootstrapTheme = new Wt::WBootstrapTheme(this);
  bootstrapTheme->setVersion(Wt::WBootstrapTheme::Version3);
  bootstrapTheme->setResponsive(true);
  setTheme(bootstrapTheme);
  useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");

  // needed to load the templates for the objects and make the bootstrap theme work
  this->messageResourceBundle().use(this->appRoot() + "text");
  
  Wt::WContainerWidget *main_container = new Wt::WContainerWidget();

  root()->addWidget( main_container );


  auto vbox = new Wt::WVBoxLayout();
  main_container->setLayout(vbox);

  auto center_container = new Wt::WContainerWidget();

  auto pb = new Wt::WPushButton("Run allocation");
  pb->clicked().connect( std::bind(  
    [=](){ 
    // TODO run the job allocation here
      system("date");
      return ; 
    })  
  );

  center_container->addWidget( pb );
  vbox->addWidget(center_container);
  center_container->setContentAlignment( AlignCenter );
  
}


WApplication *createApplication(const WEnvironment& env)
{
  std::cout << "application created" << std::endl;
  return new WebUIApplication(env);
}


int WebUI::run(int argc, char **argv)
{
  /*
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  
  worker = std::thread( WRun, argc, argv, &createApplication );

 //return WRun(argc, argv, &createApplication);
}

WebUI::~WebUI() {
  auto server = Wt::WServer::instance();
  server->stop();
  std::cout << "server stoped " << std::endl;
  if ( worker.joinable() ) {
    // TODO this might not work since the thread is executing the web server
    // which is not stopping execution if not forced to
    std::cout << "joining worker" << std::endl;
    worker.join();
  }
  std::cout << "dtor done" << std::endl;
}

