
#pragma once

#include <memory>
#include <Wt/Dbo/Dbo.h>
#include "Observer.hpp"

struct SharedData : public Observable {
  SharedData( std::shared_ptr<Wt::Dbo::Session> _session ) :
    session(_session)
  {

  }

  std::shared_ptr<Wt::Dbo::Session> session;
    
};
