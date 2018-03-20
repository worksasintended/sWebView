
#include "ReservationInfo.hpp"

#include <slurm/slurm.h>

ReservationInfo::ReservationInfo( reserve_info_t* _info ) {
  info = _info; 
}



std::string ReservationInfo::get_name(){
  return info->name;
}

