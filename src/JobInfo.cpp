

#include "JobInfo.hpp"

#include <slurm/slurm.h>

JobInfo::JobInfo( slurm_job_info_t* _info ) {
  info = _info; 
}

std::string JobInfo::get_name(){
  return info->name;
}


