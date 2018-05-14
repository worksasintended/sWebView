
#include "PartitionsInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>



void PartitionsInfo::update_data(){
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  if ( info ) {
    //clean up memory
    slurm_free_partition_info_msg(info);
  }
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  time_t last_update = 0;
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  int ret = slurm_load_partitions(last_update, &info, SHOW_FEDERATION);
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  partition_info.clear();
  for( int i = 0 ; i < this->number_of_partitions() ; i++ ) {
    std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__  << " " << i << std::endl;
    partition_info.emplace_back( &info->partition_array[i] );
    std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  }
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  this->notify_observers();
}

size_t PartitionsInfo::number_of_partitions(){
  return info->record_count;
}

PartitionInfo& PartitionsInfo::get_partition( size_t idx ) {
  return partition_info[idx];
} 
