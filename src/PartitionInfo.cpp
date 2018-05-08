#include <Wt/WApplication.h>
#include "PartitionInfo.hpp"
#include "RootApplication.hpp"

#include <slurm/slurm.h>

using namespace Wt;

PartitionInfo::PartitionInfo( partition_info_t* pinfo ) {
  info = pinfo;
  auto instance = WApplication::instance();
  auto root_app = (RootApplication*)(instance);
  auto slurm_db = root_app->get_slurm_db();
 
}



std::string PartitionInfo::get_name(){
  return info->name;
}
