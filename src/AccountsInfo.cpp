

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
  conditions->with_assocs = 0;
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
  std::cout << "done" << __PRETTY_FUNCTION__ << std::endl;
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
