
#pragma once
#include "Observable.hpp"
#include "ReservationInfo.hpp"

#include <vector>

struct reserve_info_msg;
typedef reserve_info_msg reserve_info_msg_t;

// facade class to infer data from slurm that is shown multiple times in the gui
//
struct ReservationsInfo : public Observable {
  public:
    virtual void update_data() override;

    size_t number_of_reservations();
   
    ReservationInfo& get_reservation( size_t idx );

    void create_reservation();
    void update_reservation(std::string name);

    auto begin(){
      return reservation_info.begin();
    }

    auto end() {
        return reservation_info.end();
    }

  private:
    reserve_info_msg_t* info = nullptr;
    std::vector<ReservationInfo> reservation_info; 
};


