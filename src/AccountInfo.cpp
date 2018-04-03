

#include "AccountInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>


AccountInfo::AccountInfo( void* _info ) {
  info = _info; 
}

std::string AccountInfo::get_name(){
  return ((slurmdb_account_rec_t*)info)->name;
}


