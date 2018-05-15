
#pragma once

#include <string>
#include <vector>

#include "AssociationInfo.hpp"

struct UserInfo {
  public:

    UserInfo( void* );
    ~UserInfo();

    std::string get_name() const;
    bool is_in_account( std::string account_name ) const ;
    std::vector<std::string> get_account_names() const;
    double get_fairshare();

  private:
    void* info;
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    std::vector<AssociationInfo> associations;
};


