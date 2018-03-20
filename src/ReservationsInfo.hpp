
#include "Observable.hpp"
#include "ReservationInfo.hpp"

#include <vector>

struct reserve_info_msg;
typedef reserve_info_msg reserve_info_msg_t;

// facade class to infer data from slurm that is shown multiple times in the gui
//
struct ReservationsInfo : public Observable {
  public:
    void update_data();

    size_t number_of_reservations();
   
    ReservationInfo& get_reservation( size_t idx );

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

