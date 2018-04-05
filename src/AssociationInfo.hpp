
#pragma once

#include <string>

struct AssociationInfo {
  public:

    AssociationInfo( void* );

    double get_fairshare() const;

  private:
    // cant do this with slurmdb_user_rec_t since it produces a conflicting declaration
    void* info = nullptr;
};


