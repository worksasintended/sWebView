

#include "JobsInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;

void JobsInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_job_info_msg(info);
  }
  time_t last_update = 0;
  slurm_load_jobs(last_update, &info, SHOW_FEDERATION );
  jobs_info.clear();
  for( int i = 0 ; i < this->number_of_jobs() ; i++ ) {
    jobs_info.emplace_back( &info->job_array[i] );
  }
  this->notify_observers();
}

size_t JobsInfo::number_of_jobs(){
  return info->record_count;
}

// one needs to throw an exeption if this is an out of bounds access
JobInfo& JobsInfo::get_job( size_t idx ) {
  if ( idx < 0 && idx >= jobs_info.size() ){
    throw std::out_of_range("jobs_info");
  }
  return jobs_info[idx];
}


void JobsInfo::cancel_job( const JobInfo& job_info ) {
  throw "not implemented"; 
}

