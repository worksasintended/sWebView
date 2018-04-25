
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
  if( db_conn == nullptr ) {
    std::cout << "could not establish a connection to the slurmdbd. check your slurm.conf" << std::endl;
    exit(-1);
  }
  std::cout << "slurmdb connection established" << std::endl;
}

void 
SlurmDB::disconnect(){
  slurmdb_connection_close(&db_conn);
}

void SlurmDB::update() {
  commit(false);
}

void SlurmDB::commit(bool commit) {
  auto ret = slurmdb_connection_commit(db_conn, commit);
  if ( ret != SLURM_SUCCESS ) {
    std::cout << "could not commit to slurmdb" << std::endl;
  }
}
