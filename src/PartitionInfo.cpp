#include <Wt/WApplication.h>
#include "PartitionInfo.hpp"
#include "RootApplication.hpp"

#include <slurm/slurm.h>

using namespace Wt;

PartitionInfo::PartitionInfo( partition_info_t* pinfo ) {
  info = pinfo;
}



std::string PartitionInfo::get_name(){
  return info->name;
}
