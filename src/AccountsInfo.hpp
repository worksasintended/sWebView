
#pragma once

#include "Observable.hpp"
#include "AccountInfo.hpp"
#include "SlurmDB.hpp"

#include <vector>


// facade class to infer data from slurm that is shown multiple times in the gui
//
struct AccountsInfo : public Observable {
  public:

    AccountsInfo( SlurmDB& _slurm_db ) :
      slurm_db(_slurm_db)
    {
  
    }

    virtual void update_data() override;
    size_t number_of_accounts();
    AccountInfo& get_account( size_t idx );
    void create_account( std::string name, std::string description, std::string cluster );
    void delete_account( const AccountInfo& account );

    std::vector<std::string> get_account_names();

    void print();

    auto begin(){
      return accounts_info.begin();
    }

    auto end() {
        return accounts_info.end();
    }

  private:
    std::vector<AccountInfo> accounts_info; 
    SlurmDB& slurm_db;

};


