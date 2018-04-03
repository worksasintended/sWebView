

#include "AccountsInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;


void AccountsInfo::update_data(){

  slurmdb_account_cond_t conditions;
  // zero the data block otherwise pointers dangle 
  memset(&conditions, 0, sizeof(slurmdb_user_cond_t));

  slurmdb_connection_commit(slurm_db.get_connection(), 0);
  // TODO this line leaks 
  List accounts = slurmdb_accounts_get(slurm_db.get_connection(), &conditions);

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
