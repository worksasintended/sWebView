#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "SlurmDB.hpp"

TEST_CASE( "SlurmDB connection test", "[SlurmDB]" ) {
  SlurmDB slurm_db;

  slurm_db.connect();

  slurm_db.disconnect();

}


TEST_CASE( "SlurmDB self destruct", "[SlurmDB]" ) {
  {
    SlurmDB slurm_db;

    slurm_db.connect();
  }
}
