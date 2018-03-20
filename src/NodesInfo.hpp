
#include "Observable.hpp"
#include "NodeInfo.hpp"

#include <vector>

struct node_info_msg;
typedef node_info_msg node_info_msg_t;

// facade class to infer data from slurm that is shown multiple times in the gui
//
struct NodesInfo : public Observable {
  public:
    void update_data();

    size_t number_of_nodes();
   
    NodeInfo& get_node( size_t idx );

    auto begin(){
      return node_info.begin();
    }

    auto end() {
        return node_info.end();
    }

  private:
    node_info_msg_t* info = nullptr;
    std::vector<NodeInfo> node_info; 
};


