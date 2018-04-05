
#pragma once

#include <string>
#include <vector>

#include "AssociationInfo.hpp"

struct UserInfo {
  public:

    UserInfo( void* );

    std::string get_name() const;
    bool is_in_account( std::string account_name ) const ;
    std::vector<std::string> get_account_names() const;
    double get_fairshare();

  private:
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    void* info = nullptr;
    std::vector<AssociationInfo> associations;
};


