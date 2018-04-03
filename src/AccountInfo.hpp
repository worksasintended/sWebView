
#pragma once

#include <string>


struct AccountInfo {
  public:

    AccountInfo( void* );

    std::string get_name();

  private:
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    void* info = nullptr;
};


