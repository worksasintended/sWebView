

#include "NodesInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>

void NodesInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_node_info_msg(info);
  }
  time_t last_update = 0;
  int ret = slurm_load_node(last_update, &info, SHOW_FEDERATION);
  node_info.clear();
  for( int i = 0 ; i < this->number_of_nodes() ; i++ ) {
    node_info.emplace_back( &info->node_array[i] );
  }
  std::cout << ret << std::endl;
}

size_t NodesInfo::number_of_nodes(){
  return info->record_count;
}

NodeInfo& NodesInfo::get_node( size_t idx ) {
  return node_info[idx];
}
