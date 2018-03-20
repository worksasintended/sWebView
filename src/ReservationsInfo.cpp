

#include "ReservationsInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>

void ReservationsInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_reservation_info_msg(info);
  }
  time_t last_update = 0;
  slurm_load_reservations(last_update, &info);
  reservation_info.clear();
  for( int i = 0 ; i < this->number_of_reservations() ; i++ ) {
    reservation_info.emplace_back( &info->reservation_array[i] );
  }
  this->notify_observers();
}

size_t ReservationsInfo::number_of_reservations(){
  return info->record_count;
}

ReservationInfo& ReservationsInfo::get_reservation( size_t idx ) {
  return reservation_info[idx];
}
