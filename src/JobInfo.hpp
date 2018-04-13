
#pragma once

#include <string>

struct job_info;
typedef job_info slurm_job_info_t;

struct JobInfo {
  public:

    JobInfo( slurm_job_info_t* );

    std::string get_description();
    std::string get_user_name();
    uint32_t get_id();
    std::string get_state();
    std::string get_node_list();

  private:
    slurm_job_info_t* info = nullptr;
};


