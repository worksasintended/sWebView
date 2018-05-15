


#include "ClustersInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <slurm/slurm_errno.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;


void ClustersInfo::update_data(){

  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;

  slurmdb_cluster_cond_t* conditions = 
    (slurmdb_cluster_cond_t*)xmalloc(sizeof(slurmdb_cluster_cond_t));

  slurmdb_init_cluster_cond( conditions, 0 );

  slurm_db.update();

  static List clusters;
  static bool initialized = false;

  if ( initialized ) {
    slurm_list_destroy(clusters);
  }

  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl; 
  
  clusters = slurmdb_clusters_get(slurm_db.get_connection(), conditions);
  initialized = true;

  auto it = slurm_list_iterator_create(clusters);

  clusters_info.clear();
  while ( auto element = slurm_list_next(it) ){
    std::cout << "adding cluster " << std::endl;
    clusters_info.emplace_back( element );
  }

  slurm_list_iterator_destroy(it);

  this->notify_observers();
}

size_t ClustersInfo::number_of_clusters(){
  return clusters_info.size();
}

ClusterInfo& ClustersInfo::get_cluster( size_t idx ) {
  if ( idx >= clusters_info.size() ){
    throw std::out_of_range("clusters_info");
  }
  return clusters_info[idx];
}

void ClustersInfo::print() {
  std::cout << "# " << this->number_of_clusters() << std::endl;
  for( auto& element : *this ){
    std::cout << element.get_name() << std::endl;
  }
}


