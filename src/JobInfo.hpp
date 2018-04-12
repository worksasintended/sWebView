
#pragma once

#include <string>

struct job_info;
typedef job_info slurm_job_info_t;

struct JobInfo {
  public:

    JobInfo( slurm_job_info_t* );

    std::string get_name();

  private:
    slurm_job_info_t* info = nullptr;
};


