#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "UsersInfo.hpp"

TEST_CASE( "UsersInfo update_data", "[UsersInfo]" ) {
  SlurmDB slurm_db;

  slurm_db.connect();

  UsersInfo users_info(slurm_db);

  users_info.update_data();

  slurm_db.disconnect();
}

TEST_CASE( "UsersInfo add, find and remove user", "[UsersInfo]" ) {
  SlurmDB slurm_db;

  slurm_db.connect();

  UsersInfo users_info(slurm_db);

  users_info.add_user("example_user", "root" );

  bool found = false;
  for( auto& user : users_info ){
    if ( user.get_name() == "example_user" ) {
      found = true;
    }
  }
  
  REQUIRE( found == true );

  users_info.remove_user("example_user" );

  slurm_db.disconnect();
}
