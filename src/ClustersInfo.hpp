

#pragma once

#include "Observable.hpp"
#include "ClusterInfo.hpp"
#include "SlurmDB.hpp"

#include <vector>


// facade class to infer data from slurm that is shown multiple times in the gui
//
struct ClustersInfo : public Observable {
  public:

    ClustersInfo( SlurmDB& _slurm_db ) :
      slurm_db(_slurm_db)
    {
  
    }

    void update_data();
    size_t number_of_clusters();
    ClusterInfo& get_cluster( size_t idx );

    void print();

    auto begin(){
      return clusters_info.begin();
    }

    auto end() {
        return clusters_info.end();
    }

  private:

    std::vector<ClusterInfo> clusters_info; 
    SlurmDB& slurm_db;

};


