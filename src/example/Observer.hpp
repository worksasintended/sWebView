#pragma once

#include <set>


struct Observer {
  virtual void update() = 0;
};

struct Observable {

  public:
    void add_observer( Observer* o ) {
      observers.insert( o );
    }

    void remove_observer( Observer* o)
    {
      observers.erase( o );
    }

    void notify_observers()
    {
      for( auto& o : observers ){
        o->update();
      }
    }

  private:
    std::set<Observer*> observers;
};
