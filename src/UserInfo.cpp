

#include "UserInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>


UserInfo::UserInfo( void* _info ) {
  info = _info; 
}

std::string UserInfo::get_name() const{
  if ( info == nullptr ) return "no info item";
  if ( ((slurmdb_user_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_user_rec_t*)info)->name;
}


