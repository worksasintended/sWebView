

#include "UserInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>

using namespace std;


UserInfo::UserInfo( void* _info ) {
  info = _info; 
}

std::string UserInfo::get_name() const{
  if ( info == nullptr ) return "no info item";
  if ( ((slurmdb_user_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_user_rec_t*)info)->name;
}

#if 0
void UserInfo::for_all_accounts( std::function<void(slurmdb_assoc_rec_t* )> ) {
  
}
#endif

bool UserInfo::is_in_account( std::string account_name ) const{
  auto user = (slurmdb_user_rec_t*)info;
  bool is = false;

  if ( !user->assoc_list ) {
    std::cout << "assoc list empty did you forget to set with_assocs = 1 " << std::endl;
    return true;
  }

  auto it = slurm_list_iterator_create(user->assoc_list);

  std::cout << "searching for account name " << account_name << std::endl;

  while( auto element = slurm_list_next( it ) ){
    auto association = (slurmdb_assoc_rec_t*)element;
    std::string name = association->acct;
    std::cout << "name: " << name << std::endl;
    if ( name == account_name ) {
      is = true;
      break;
    }
  }

  slurm_list_iterator_destroy( it );

  return is;
}

