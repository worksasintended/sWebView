
#pragma once

#include <string>
#include <vector>

#include "AssociationInfo.hpp"


struct AccountInfo {
  public:

    AccountInfo( void* );

    std::string get_name() const;
    double get_fairshare() const;

  private:
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    void* info = nullptr;
    std::vector<AssociationInfo> associations;
};


