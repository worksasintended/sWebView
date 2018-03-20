
#include "PartitionInfo.hpp"

#include <slurm/slurm.h>

PartitionInfo::PartitionInfo( partition_info_t* pinfo ) {
  info = pinfo; 
}



std::string PartitionInfo::get_name(){
  return info->name;
}
