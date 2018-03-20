#pragma once
#include <Wt/WContainerWidget.h>
#include <slurm/slurm.h>

#include "Observable.hpp"


// facade class to infer data from slurm that is shown multiple times in the gui
//
struct PartitionsInfoData : public Observable {
  public:
    void update_data(){
      if ( info ) {
        //clean up memory
        slurm_free_partition_info_msg(info);
      }
      time_t last_update = 0;
      int ret = slurm_load_partitions(last_update, &info, SHOW_FEDERATION);
      std::cout << ret << std::endl;
    }

    auto number_of_partitions(){
      return info->record_count;
    }
   
    // one could create a PartitionInfoData class ("NOTE without the s") to manage the 
    // information of a single partition but this could be overkill 
    std::string get_partition_name( int idx ) {
      return info->partition_array[idx].name;
    } 

  private:
    partition_info_msg_t* info = nullptr;
};

class InfoWidget : public Wt::WContainerWidget, public Observer {
public:
    InfoWidget ();
    virtual ~InfoWidget ();
    virtual void update() override;

private:
    PartitionsInfoData* partitions_info_data = nullptr; // perhaps make this a shared_ptr
};

