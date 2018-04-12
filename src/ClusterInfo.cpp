

#include "ClusterInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>
#include <iostream>

using namespace std;


ClusterInfo::ClusterInfo( void* _info ) {
  info = _info; 

  auto cluster = (slurmdb_cluster_rec_t*)info;

}

std::string ClusterInfo::get_name() const{
  if ( info == nullptr ) return "no info item";
  if ( ((slurmdb_cluster_rec_t*)info)->name == nullptr ) return "no name";
  return ((slurmdb_cluster_rec_t*)info)->name;
}

