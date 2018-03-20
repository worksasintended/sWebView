
#include "NodeInfo.hpp"

#include <slurm/slurm.h>

NodeInfo::NodeInfo( node_info_t* _info ) {
  info = _info; 
}



std::string NodeInfo::get_name(){
  return info->name;
}

size_t NodeInfo::get_cpus(){
  return info->cpus;
}
