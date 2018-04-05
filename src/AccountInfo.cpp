

#include "AccountInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>


AccountInfo::AccountInfo( void* _info ) {
  info = _info; 
  auto account = (slurmdb_account_rec_t*)info;

  for_all<slurmdb_assoc_rec_t>( account->assoc_list, [&]( auto assoc_rec ){ 
    associations.emplace_back( assoc_rec );
  });
}

std::string AccountInfo::get_name() const{
  if ( info == nullptr ) return "no info item";
  if ( ((slurmdb_account_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_account_rec_t*)info)->name;
}

double AccountInfo::get_fairshare() const{
  return 0;
  double ret = 0;
  for( auto& association : associations ){
    ret += association.get_fairshare();
  }
  return ret;
}
