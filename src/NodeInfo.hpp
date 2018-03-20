#pragma once

#include <string>

struct node_info;
typedef node_info node_info_t;

struct NodeInfo {
  public:

    NodeInfo( node_info_t* );

    std::string get_name();
    size_t get_cpus();

  private:
    node_info_t* info = nullptr;
};


