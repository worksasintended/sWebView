

#include "UserInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>

using namespace std;

UserInfo::UserInfo( void* _info ) {

  if ( _info == nullptr ) {
    std::cout << "given info object is nullptr" << std::endl;
    exit(EXIT_FAILURE);
  }

  info = _info;

  for_all<slurmdb_assoc_rec_t>( ((slurmdb_user_rec_t*)info)->assoc_list, [&]( auto assoc_rec ){ 
    associations.emplace_back( assoc_rec );
  });

}

UserInfo::~UserInfo(){
}

std::string UserInfo::get_name() const{
  if ( ((slurmdb_user_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_user_rec_t*)info)->name;
}

bool UserInfo::is_in_account( std::string account_name ) const{
  auto user = ((slurmdb_user_rec_t*)info);
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

  auto user = ((slurmdb_user_rec_t*)info);

  for_all<slurmdb_assoc_rec_t>( user->assoc_list, [&](slurmdb_assoc_rec_t* association){ 
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
