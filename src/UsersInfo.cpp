

#include "UsersInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;


void UsersInfo::update_data(){

  slurmdb_user_cond_t conditions;
  // zero the data block otherwise pointers dangle 
  memset(&conditions, 0, sizeof(slurmdb_user_cond_t));

  slurmdb_connection_commit(slurm_db.get_connection(), 0);
  // TODO this line leaks 
  List users = slurmdb_users_get(slurm_db.get_connection(), &conditions);

  auto it = slurm_list_iterator_create(users);

  users_info.clear();
  while ( auto element = slurm_list_next(it) ){
    users_info.emplace_back( element );
  }

  slurm_list_iterator_destroy(it);

  this->notify_observers();
}

size_t UsersInfo::number_of_users(){
  return users_info.size();
}

UserInfo& UsersInfo::get_users( size_t idx ) {
  if ( idx < 0 && idx >= users_info.size() ){
    throw std::out_of_range("users_info");
  }
  return users_info[idx];
}

void UsersInfo::print() {
  std::cout << "# " << this->number_of_users() << std::endl;
  for( auto& element : *this ){
    std::cout << element.get_name() << std::endl;
  }
}
