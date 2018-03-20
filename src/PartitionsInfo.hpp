#pragma once

#include "Observable.hpp"
#include "PartitionInfo.hpp"

#include <vector>

struct partition_info_msg;
typedef partition_info_msg partition_info_msg_t;

// facade class to infer data from slurm that is shown multiple times in the gui
//
struct PartitionsInfo : public Observable {
  public:
    void update_data();

    size_t number_of_partitions();
   
    PartitionInfo& get_partition( size_t idx );

    auto begin(){
      return partition_info.begin();
    }

    auto end() {
        return partition_info.end();
    }

  private:
    partition_info_msg_t* info = nullptr;
    std::vector<PartitionInfo> partition_info; 
};


