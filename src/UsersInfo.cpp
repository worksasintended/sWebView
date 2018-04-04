

#include "UsersInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;


void UsersInfo::update_data(){

  slurmdb_user_cond_t* conditions = 
    (slurmdb_user_cond_t*)xmalloc(sizeof(slurmdb_user_cond_t));

  conditions->assoc_cond = (slurmdb_assoc_cond_t*)xmalloc(sizeof(slurmdb_assoc_cond_t));

  // TODO SlurmDB
  slurmdb_connection_commit(slurm_db.get_connection(), 0);
  static List users;
  static bool initialized = false;

  if ( initialized ) {
    slurm_list_destroy(users);
  }
  
  users = slurmdb_users_get(slurm_db.get_connection(), conditions);
  initialized = true;

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

// TODO first one needs to check wether the user already is in the group one
// wants to make default
void UsersInfo::set_default_account( const UserInfo& user_info, std::string default_account ){
  slurmdb_user_cond_t user_cond;
  memset(&user_cond, 0, sizeof(decltype(user_cond)));
  slurmdb_user_rec_t user;
  memset(&user, 0, sizeof(decltype(user)));

  user_cond.assoc_cond = (slurmdb_assoc_cond_t*)malloc(sizeof(slurmdb_assoc_cond_t));
  user_cond.assoc_cond->cluster_list = slurm_list_create(slurm_destroy_char);
  /*
   * FROM: sacctmgr user_functions.c
   * We need this to make sure we only change users, not
   * accounts if this list didn't exist it would change
   * accounts. Having it blank is fine, it just needs to
   * exist. 
   */
  user_cond.assoc_cond->user_list = slurm_list_create(slurm_destroy_char);

  // specify the name
  slurm_list_append( user_cond.assoc_cond->user_list, strdup(user_info.get_name().c_str()) );
  //slurm_addto_char_list(user_cond.assoc_cond->user_list, user_info.get_name() );

  // specify the account to go to 
  // you already need to have this in the list of accounts you are in
  user.default_acct = strdup(default_account.c_str());

  List ret_list = slurmdb_users_modify(slurm_db.get_connection(), &user_cond, &user);

  if( ret_list ){
    std::cout << "something changed" << std::endl;
  }else{
    std::cout << "error setting values" << std::endl;
  }

  slurm_list_destroy(ret_list);
  this->notify_observers();
}
















