
#include "SlurmDB.hpp"
#include <slurm/slurmdb.h>
#include <iostream>

using namespace std;

SlurmDB::SlurmDB (){

}

SlurmDB::~SlurmDB (){

}

void 
SlurmDB::connect(){
  db_conn = slurmdb_connection_get();
  if ( errno != SLURM_SUCCESS) {
    std::cout << "error in slurm connection establish" << std::endl;
  }
  std::cout << "slurmdb connection established" << std::endl;
}

void 
SlurmDB::disconnect(){
  slurmdb_connection_close(&db_conn);
}
