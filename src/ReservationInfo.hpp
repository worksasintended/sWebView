#pragma once

#include <string>

struct reserve_info;
typedef reserve_info reserve_info_t;

struct ReservationInfo {
  public:

    ReservationInfo( reserve_info_t* );

    std::string get_name();
    std::string get_start_time_string();
    std::string get_end_time_string();
    std::string get_users();

  private:
    reserve_info_t* info = nullptr;
};


