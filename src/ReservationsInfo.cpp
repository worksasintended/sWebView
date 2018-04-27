

#include "ReservationsInfo.hpp"
#include "SlurmInternal.hpp"

#include <slurm/slurm.h>
#include <iostream>
#include <chrono>
#include <memory>
#include <cstring>

using namespace std;

void ReservationsInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_reservation_info_msg(info);
  }
  time_t last_update = 0;
  slurm_load_reservations(last_update, &info);
  reservation_info.clear();
  for( int i = 0 ; i < info->record_count ; i++ ) {
    reservation_info.emplace_back( &info->reservation_array[i] );
  }
  this->notify_observers();
}

size_t ReservationsInfo::number_of_reservations(){
  return reservation_info.size();
}

// one needs to throw an exeption if this is an out of bounds access
ReservationInfo& ReservationsInfo::get_reservation( size_t idx ) {
  if ( idx < 0 && idx >= reservation_info.size() ){
    throw std::out_of_range("reservation_info");
  }
  return reservation_info[idx];
}


void ReservationsInfo::create_reservation(){
  unique_ptr<resv_desc_msg_t> desc_msg( new resv_desc_msg_t ); // we own the struct so we need to destroy it

  slurm_init_resv_desc_msg( desc_msg.get() ); // initialize with defaults
#if 0
  	char *accounts;		/* names of accounts permitted to use */
	char *burst_buffer;	/* burst buffer resources to be included */
	uint32_t *core_cnt;	/* Count of cores required */
	uint32_t duration;	/* duration of reservation in minutes */
	time_t end_time;	/* end time of reservation */
	char *features;		/* required node features */
	uint64_t flags;		/* see RESERVE_FLAG_* above */
	char *licenses;		/* names of licenses to be reserved */
	char *name;		/* name of reservation (optional on create) */
	uint32_t *node_cnt;	/* Count of nodes required. Specify set of job
				 * sizes with trailing zero to optimize layout
				 * for those jobs just specify their total size
				 * to ignore optimized topology. For example,
				 * {512,512,1024,0} OR {2048,0}. */
	char *node_list;	/* list of reserved nodes or ALL */
	char *partition;	/* name of partition to be used */
	time_t start_time;	/* start time of reservation */
	uint32_t resv_watts;    /* amount of power to reserve  */
	char *tres_str;         /* list of TRES's used by reservation */
	char *users;		/* names of users permitted to use */ 
#endif
  // TODO this is just an example implementation 
  // all other values have to be obtained from the user interface
  desc_msg->start_time = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now());
  desc_msg->accounts = xstrdup("root");
  desc_msg->end_time = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now() + std::chrono::hours(24));

  slurm_create_reservation(desc_msg.get());
  // changed the underlying data model so an update is needed 
  this->update_data();
}

void ReservationsInfo::update_reservation(std::string name){
  unique_ptr<resv_desc_msg_t> desc_msg( new resv_desc_msg_t ); // we own the struct so we need to destroy it
  slurm_init_resv_desc_msg( desc_msg.get() ); // initialize with defaults

  desc_msg->name = xstrdup(name.c_str());

  slurm_update_reservation(desc_msg.get());
  this->update_data();
}









