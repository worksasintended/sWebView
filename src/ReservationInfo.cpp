
#include "ReservationInfo.hpp"
#include <ctime>
#include <slurm/slurm.h>
#include "SlurmInternal.hpp"

ReservationInfo::ReservationInfo( reserve_info_t* _info ) {
  info = _info; 
}



std::string ReservationInfo::get_name(){
  return to_str(info->name);
}

std::string ReservationInfo::get_start_time_string(){
	time_t time_t_var = info->end_time;
	std::string start_time_string;
  if ( time_t_var > 0 ) {
      start_time_string = std::ctime(&time_t_var);
  }
  return start_time_string;
}
std::string ReservationInfo::get_end_time_string(){
	time_t time_t_var = info->end_time;
	std::string end_time_string;
  if ( time_t_var > 0 ) {
      end_time_string = std::ctime(&time_t_var);
  }
  return end_time_string;
}
std::string ReservationInfo::get_users(){
	return to_str(info->users);
}
