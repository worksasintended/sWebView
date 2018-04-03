

#include "UserInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>


UserInfo::UserInfo( void* _info ) {
  info = _info; 
}

std::string UserInfo::get_name(){
  return ((slurmdb_user_rec_t*)info)->name;
}


