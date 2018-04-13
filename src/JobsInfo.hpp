

#pragma once

#include "Observable.hpp"
#include "JobInfo.hpp"
#include "SlurmDB.hpp"

#include <vector>


struct job_info_msg;
typedef job_info_msg job_info_msg_t;

struct JobsInfo : public Observable {
  public:

    JobsInfo( ) = default;

    void update_data();
    size_t number_of_jobs();
    JobInfo& get_job( size_t idx );
    void cancel_job( const JobInfo& );

    void print();

    auto begin(){
      return jobs_info.begin();
    }

    auto end() {
        return jobs_info.end();
    }

  private:

    std::vector<JobInfo> jobs_info; 
    job_info_msg_t* info;

};


