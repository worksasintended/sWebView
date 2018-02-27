
#pragma once
#include <set>

class Observer {
public:
  virtual void update() = 0;
};

class Observable {
public:
  void notify_observers() {
    for( auto& observer : observers ){
      observer->update();
    }
    
  }
  void add_observer( Observer* o ) {
    observers.insert(o);
  }

  void remove_observer( Observer* o ) {
    observers.erase(o);
  }

private:
  std::set<Observer*> observers;
};
