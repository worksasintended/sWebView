
#include <string>

struct partition_info;
typedef partition_info partition_info_t;

struct PartitionInfo {
  public:

    PartitionInfo( partition_info_t* );

    std::string get_name();

  private:
    partition_info_t* info = nullptr;
};


