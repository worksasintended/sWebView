

#include "UserInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>

using namespace std;


UserInfo::UserInfo( void* _info ) {
  info = _info; 

  auto user = (slurmdb_user_rec_t*)info;

  for_all<slurmdb_assoc_rec_t>( user->assoc_list, [&]( auto assoc_rec ){ 
    associations.emplace_back( assoc_rec );
  });

}

std::string UserInfo::get_name() const{
  if ( info == nullptr ) return "no info item";
  if ( ((slurmdb_user_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_user_rec_t*)info)->name;
}

void for_all_accounts( slurmdb_user_rec_t* user, std::function<void(slurmdb_assoc_rec_t* )> f) {

  if ( !user->assoc_list ) {
    std::cout << "user assoc list is empty -> proceeding" << std::endl;
    return;
  }

  auto it = slurm_list_iterator_create(user->assoc_list);

  while( auto element = slurm_list_next( it ) ){
    auto association = (slurmdb_assoc_rec_t*)element;
    f( association );
  }

  slurm_list_iterator_destroy( it ); 
}

bool UserInfo::is_in_account( std::string account_name ) const{
  auto user = (slurmdb_user_rec_t*)info;
  bool is = false;

  if ( !user->assoc_list ) {
    std::cout << "assoc list empty did you forget to set with_assocs = 1 " << std::endl;
    return true;
  }

  auto it = slurm_list_iterator_create(user->assoc_list);

  while( auto element = slurm_list_next( it ) ){
    auto association = (slurmdb_assoc_rec_t*)element;
    std::string name = association->acct;
    if ( name == account_name ) {
      is = true;
      break;
    }
  }

  slurm_list_iterator_destroy( it );

  return is;
}


std::vector<std::string> UserInfo::get_account_names() const {
  std::vector<std::string> ret;
  for_all_accounts( (slurmdb_user_rec_t*)info,  [&](slurmdb_assoc_rec_t* association){ 
    ret.emplace_back( association->acct );
  });
  return ret;
}

double UserInfo::get_fairshare() {
  double ret = 0;
  for( auto& association : associations ){
    ret += association.get_fairshare();
  }
  return ret;
}
