

#include "AssociationInfo.hpp"

#include <slurm/slurm.h>
#include <slurm/slurmdb.h>

#include <iostream>

using namespace std;


AssociationInfo::AssociationInfo( void* _info ) {
  if ( _info == nullptr ) {
    std::cout << "trying to store nullptr in AssociationInfo" << std::endl;
    exit(-1);
  }
  info = _info; 
}

double AssociationInfo::get_fairshare() const{
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  auto assoc = (slurmdb_assoc_rec_t*)info;
  if ( info == nullptr ) {
    std::cout << "info is null" << std::endl;
    exit(1);
  }
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  if ( assoc == nullptr ) exit(2);
  std::cout << __PRETTY_FUNCTION__ << " " << __FILE__ << " " << __LINE__ << std::endl;
  std::cout << "assoc " << assoc  << std::endl;
  std::cout << "assoc->usage " << assoc->usage  << std::endl;
  return assoc->usage->fs_factor;
}
