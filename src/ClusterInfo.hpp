

#pragma once

#include <string>
#include <vector>

struct ClusterInfo {
  public:

    ClusterInfo( void* );

    std::string get_name() const;

  private:
    void* info = nullptr;
};


