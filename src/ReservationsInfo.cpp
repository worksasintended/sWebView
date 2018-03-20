

#include "ReservationsInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>
#include <chrono>
#include <memory>

using namespace std;

void ReservationsInfo::update_data(){
  if ( info ) {
    //clean up memory
    slurm_free_reservation_info_msg(info);
  }
  time_t last_update = 0;
  slurm_load_reservations(last_update, &info);
  reservation_info.clear();
  for( int i = 0 ; i < this->number_of_reservations() ; i++ ) {
    reservation_info.emplace_back( &info->reservation_array[i] );
  }
  this->notify_observers();
}

size_t ReservationsInfo::number_of_reservations(){
  return info->record_count;
}

ReservationInfo& ReservationsInfo::get_reservation( size_t idx ) {
  return reservation_info[idx];
}


void ReservationsInfo::create_reservation(){
  unique_ptr<resv_desc_msg_t> desc_msg( new resv_desc_msg_t );
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
  desc_msg->accounts = (char*)malloc(sizeof(char)*200);
  sprintf( desc_msg->accounts, "root");
  desc_msg->end_time = std::chrono::system_clock::to_time_t(std::chrono::high_resolution_clock::now() + std::chrono::hours(24));

  slurm_create_reservation(desc_msg);
}
