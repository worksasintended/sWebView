

#include "AccountsInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>


using namespace std;
void AccountsInfo::update_data(){

  slurmdb_account_cond_t* conditions = 
    (slurmdb_account_cond_t*)xmalloc(sizeof(slurmdb_account_cond_t));

  conditions->assoc_cond = (slurmdb_assoc_cond_t*)xmalloc(sizeof(slurmdb_assoc_cond_t));
  conditions->with_assocs = 1;
  //conditions->assoc_cond->with_usage = 1;
  //conditions->assoc_cond->usage_start = 0 ;
  //conditions->assoc_cond->usage_end = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
  conditions->assoc_cond->cluster_list = slurm_list_create(slurm_destroy_char);

  slurm_db.update();

  static List accounts;
  static bool initialized = false;

  if ( initialized ) {
    slurm_list_destroy(accounts);
  }

  accounts = slurmdb_accounts_get(slurm_db.get_connection(), conditions);
  initialized = true;

  auto it = slurm_list_iterator_create(accounts);

  accounts_info.clear();
  while ( auto element = slurm_list_next(it) ){
    accounts_info.emplace_back( element );
  }

  slurm_list_iterator_destroy(it);

  this->notify_observers();
}

size_t AccountsInfo::number_of_accounts(){
  return accounts_info.size();
}

AccountInfo& AccountsInfo::get_account( size_t idx ) {
  if ( idx < 0 && idx >= accounts_info.size() ){
    throw std::out_of_range("accounts_info");
  }
  return accounts_info[idx];
}

void AccountsInfo::print() {
  std::cout << "# " << this->number_of_accounts() << std::endl;
  for( auto& element : *this ){
    std::cout << element.get_name() << std::endl;
  }
}


std::vector<std::string> 
AccountsInfo::get_account_names(){
  std::vector<std::string> names;
  for( auto& account : *this ){
    names.push_back( account.get_name() ) ;
  }
  return names;
}

void AccountsInfo::create_account( std::string name, std::string description, std::string cluster ) {
  auto account = slurm_malloc<slurmdb_account_rec_t>();
  
  account->name = xstrdup( name.c_str() );
  account->description = xstrdup( description.c_str() );
  account->organization = xstrdup(name.c_str());

  auto assoc = slurm_malloc<slurmdb_assoc_rec_t>();
  slurmdb_init_assoc_rec(assoc, 0);

  assoc->acct = xstrdup( name.c_str() );
  assoc->cluster = xstrdup(cluster.c_str());

  account->assoc_list = slurm_list_create(slurmdb_destroy_assoc_rec);
  slurm_list_append( account->assoc_list, assoc );

  auto account_list = slurm_list_create(slurmdb_destroy_account_rec);
  slurm_list_append( account_list, account );


  int ret = slurmdb_accounts_add(slurm_db.get_connection(), account_list);

  if ( ret != SLURM_SUCCESS ) {
    throw "Unknown: could create account";
  }

  slurm_db.commit();
  this->update_data();
}



void AccountsInfo::delete_account( const AccountInfo& account ){

  auto account_cond = slurm_malloc<slurmdb_account_cond_t>();
  
  account_cond->assoc_cond = slurm_malloc<slurmdb_assoc_cond_t>();

  account_cond->assoc_cond->acct_list = slurm_list_create(slurm_destroy_char);
  slurm_list_append( account_cond->assoc_cond->acct_list , xstrdup(account.get_name().c_str() ));

  slurmdb_accounts_remove(slurm_db.get_connection(), account_cond );

  slurm_db.commit();
  this->update_data();
}










