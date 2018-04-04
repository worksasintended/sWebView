
#include "SlurmDB.hpp"
#include <slurm/slurmdb.h>
#include <slurm/slurm_errno.h>
#include <iostream>

using namespace std;

SlurmDB::SlurmDB (){

}

SlurmDB::~SlurmDB (){

}

void 
SlurmDB::connect(){
  db_conn = slurmdb_connection_get();
  if ( slurm_get_errno() != SLURM_SUCCESS) {
    std::cout << "error in slurm connection establish" << std::endl;
    exit(-1);
  }
  std::cout << "slurmdb connection established" << std::endl;
  sleep(1);
}

void 
SlurmDB::disconnect(){
  slurmdb_connection_close(&db_conn);
}
