
#pragma once

#include "Observable.hpp"
#include "UserInfo.hpp"
#include "SlurmDB.hpp"

#include <vector>


// facade class to infer data from slurm that is shown multiple times in the gui
//
struct UsersInfo : public Observable {
  public:

    UsersInfo( SlurmDB& _slurm_db ) :
      slurm_db(_slurm_db)
    {
  
    }

    void update_data();
    size_t number_of_users();
    UserInfo& get_users( size_t idx );
    void set_default_account( const UserInfo& user_info, std::string default_account );
    void add_to_account( const UserInfo& user_info, std::string account );

    void print();

    auto begin(){
      return users_info.begin();
    }

    auto end() {
        return users_info.end();
    }

  private:

    std::vector<UserInfo> users_info; 
    SlurmDB& slurm_db;

};


