
#include "PartitionsInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>



void PartitionsInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_partition_info_msg(info);
  }
  time_t last_update = 0;
  int ret = slurm_load_partitions(last_update, &info, SHOW_FEDERATION);
  partition_info.clear();
  for( int i = 0 ; i < this->number_of_partitions() ; i++ ) {
    partition_info.emplace_back( &info->partition_array[i] );
  }
  this->notify_observers();
}

size_t PartitionsInfo::number_of_partitions(){
  return info->record_count;
}

PartitionInfo& PartitionsInfo::get_partition( size_t idx ) {
  return partition_info[idx];
} 
