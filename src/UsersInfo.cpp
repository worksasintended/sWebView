

#include "UsersInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <slurm/slurm_errno.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;


void UsersInfo::update_data(){

  slurmdb_user_cond_t* conditions = 
    (slurmdb_user_cond_t*)xmalloc(sizeof(slurmdb_user_cond_t));

  conditions->assoc_cond = (slurmdb_assoc_cond_t*)xmalloc(sizeof(slurmdb_assoc_cond_t));
  conditions->with_assocs = 1;

  slurm_db.update();

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


// this should be the functionality of 
// sacctmgr modify user where Names=user_info.get_name() set DefaultAccount=default_account
void UsersInfo::set_default_account( const UserInfo& user_info, std::string default_account ){

  if ( !user_info.is_in_account( default_account ) ) {
    throw std::invalid_argument(
        "Can not set to default account "
        "since the user does not list this account as one of his/her accounts"
    );
  }

  slurmdb_user_cond_t* user_cond = 
    (slurmdb_user_cond_t*)xmalloc(sizeof(slurmdb_user_cond_t));

  user_cond->assoc_cond = (slurmdb_assoc_cond_t*)xmalloc(sizeof(slurmdb_assoc_cond_t));
  user_cond->assoc_cond->cluster_list = slurm_list_create(slurm_destroy_char);
  /*
   * FROM: sacctmgr user_functions.c
   * We need this to make sure we only change users, not
   * accounts if this list didn't exist it would change
   * accounts. Having it blank is fine, it just needs to
   * exist. 
   */
  user_cond->assoc_cond->user_list = slurm_list_create(slurm_destroy_char);

  // specify the name
  slurm_list_append( user_cond->assoc_cond->user_list, xstrdup(user_info.get_name().c_str()) );

  slurmdb_user_rec_t* user = (slurmdb_user_rec_t*)xmalloc(sizeof(slurmdb_user_rec_t));
  // specify the account to go to 
  // you already need to have this in the list of accounts you are in
  user->default_acct = xstrdup(default_account.c_str());

  List ret_list = slurmdb_users_modify(slurm_db.get_connection(), user_cond, user);

  if ( slurm_get_errno() != SLURM_SUCCESS ) {
    std::cout << "errno " << errno  << std::endl;
  }

  if( ret_list ){
    std::cout << "something changed" << std::endl;
    auto n = list_count( ret_list );
    std::cout << n << " lines affected" << std::endl;
  }else{
    std::cout << "error setting values" << std::endl;
  }

  // important !!!!!!! commit all things you changed in this transaction
  slurm_db.commit();

  slurm_list_destroy(ret_list);
  update_data();
}


// TODO check wether this is nessecary 
void UsersInfo::add_to_account( const UserInfo& user_info, std::string account ){

  auto user = slurm_malloc<slurmdb_user_rec_t>();
  auto assoc = slurm_malloc<slurmdb_assoc_rec_t>();
  slurmdb_init_assoc_rec(assoc, 0);
  
  assoc->acct = xstrdup(account.c_str());
  assoc->user = xstrdup(user_info.get_name().c_str());

  // TODO have to wrap cluster to get information from this
  assoc->cluster = xstrdup("linux");

  user->assoc_list = slurm_list_create(slurmdb_destroy_assoc_rec);
  user->name = xstrdup(user_info.get_name().c_str());

  slurm_list_append( user->assoc_list, assoc );

  auto user_list = slurm_list_create(slurmdb_destroy_user_rec);
  slurm_list_append( user_list, user );

  int ret = slurmdb_users_add( slurm_db.get_connection(), user_list );

  if ( ret != SLURM_SUCCESS ) {
    throw "Unknown: could not add the user to the account";
  }

  // important !!!!!!! commit all things you changed in this transaction
  slurm_db.commit();

  update_data();
}














