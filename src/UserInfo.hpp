
#pragma once

#include <string>


struct UserInfo {
  public:

    UserInfo( void* );

    std::string get_name() const;
    bool is_in_account( std::string account_name ) const ;

  private:
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    void* info = nullptr;
};


