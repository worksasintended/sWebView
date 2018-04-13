

#include "JobInfo.hpp"

#include <slurm/slurm.h>
#include <iostream>

using namespace std;

#if 0

typedef struct job_info {
	char *account;		/* charge to specified account */
	char *admin_comment;	/* administrator's arbitrary comment */
	char    *alloc_node;	/* local node making resource alloc */
	uint32_t alloc_sid;	/* local sid making resource alloc */
	void *array_bitmap;	/* NOTE: set on unpack */
	uint32_t array_job_id;	/* job_id of a job array or 0 if N/A */
	uint32_t array_task_id;	/* task_id of a job array */
	uint32_t array_max_tasks; /* Maximum number of running tasks */
	char *array_task_str;	/* string expression of task IDs in this record */
	uint32_t assoc_id;	/* association id for job */
	char *batch_features;	/* features required for batch script's node */
	uint16_t batch_flag;	/* 1 if batch: queued job with script */
	char *batch_host;	/* name of host running batch script */
	uint32_t bitflags;      /* Various job flags */
	uint16_t boards_per_node;  /* boards per node required by job   */
	char *burst_buffer;	/* burst buffer specifications */
	char *burst_buffer_state; /* burst buffer state info */
	char *cluster;		/* name of cluster that the job is on */
	char *cluster_features;	/* comma separated list of required cluster
				 * features */
	char *command;		/* command to be executed, built from submitted
				 * job's argv and NULL for salloc command */
	char *comment;		/* arbitrary comment */
	uint16_t contiguous;	/* 1 if job requires contiguous nodes */
	uint16_t core_spec;	/* specialized core count */
	uint16_t cores_per_socket; /* cores per socket required by job  */
	double billable_tres;	/* billable TRES cache. updated upon resize */
	uint16_t cpus_per_task;	/* number of processors required for
				 * each task */
	uint32_t cpu_freq_min;  /* Minimum cpu frequency  */
	uint32_t cpu_freq_max;  /* Maximum cpu frequency  */
	uint32_t cpu_freq_gov;  /* cpu frequency governor */
	char *cpus_per_tres;	/* semicolon delimited list of TRES=# values */
	time_t deadline;	/* deadline */
	uint32_t delay_boot;	/* delay boot for desired node state */
	char *dependency;	/* synchronize job execution with other jobs */
	uint32_t derived_ec;	/* highest exit code of all job steps */
	time_t eligible_time;	/* time job is eligible for running */
	time_t end_time;	/* time of termination, actual or expected */
	char *exc_nodes;	/* comma separated list of excluded nodes */
	int32_t *exc_node_inx;	/* excluded list index pairs into node_table:
				 * start_range_1, end_range_1,
				 * start_range_2, .., -1  */
	uint32_t exit_code;	/* exit code for job (status from wait call) */
	char *features;		/* comma separated list of required features */
	char *fed_origin_str;	/* Origin cluster's name */
	uint64_t fed_siblings_active;  /* bitmap of active fed sibling ids */
	char *fed_siblings_active_str; /* string of active sibling names */
	uint64_t fed_siblings_viable;  /* bitmap of viable fed sibling ids */
	char *fed_siblings_viable_str; /* string of viable sibling names */
	char *gres;		/* comma separated list of generic resources */
	uint32_t gres_detail_cnt; /* Count of gres_detail_str records,
				 * one per allocated node */
	char **gres_detail_str;	/* Details of GRES index alloc per node */
	uint32_t group_id;	/* group job submitted as */
	uint32_t job_id;	/* job ID */
	job_resources_t *job_resrcs; /* opaque data type, job resources */
	uint32_t job_state;	/* state of the job, see enum job_states */
	time_t last_sched_eval; /* last time job was evaluated for scheduling */
	char *licenses;		/* licenses required by the job */
	uint32_t max_cpus;	/* maximum number of cpus usable by job */
	uint32_t max_nodes;	/* maximum number of nodes usable by job */
	char *mcs_label;	/* mcs_label if mcs plugin in use */
	char *mem_per_tres;	/* semicolon delimited list of TRES=# values */
	char *name;		/* name of the job */
	char *network;		/* network specification */
	char *nodes;		/* list of nodes allocated to job */
	uint32_t nice;	  	/* requested priority change */
	int32_t *node_inx;	/* list index pairs into node_table for *nodes:
				 * start_range_1, end_range_1,
				 * start_range_2, .., -1  */
	uint16_t ntasks_per_core;/* number of tasks to invoke on each core */
	uint16_t ntasks_per_node;/* number of tasks to invoke on each node */
	uint16_t ntasks_per_socket;/* number of tasks to invoke on each socket*/
	uint16_t ntasks_per_board; /* number of tasks to invoke on each board */
	uint32_t num_cpus;	/* minimum number of cpus required by job */
	uint32_t num_nodes;	/* minimum number of nodes required by job */
	uint32_t num_tasks;	/* requested task count */
	uint32_t pack_job_id;	/* lead job ID of pack job leader */
	char *pack_job_id_set;	/* job IDs for all components */
	uint32_t pack_job_offset; /* pack job index */
	char *partition;	/* name of assigned partition */
	uint64_t pn_min_memory; /* minimum real memory per node, default=0 */
	uint16_t pn_min_cpus;   /* minimum # CPUs per node, default=0 */
	uint32_t pn_min_tmp_disk; /* minimum tmp disk per node, default=0 */
	uint8_t power_flags;	/* power management flags,
				 * see SLURM_POWER_FLAGS_ */
	time_t preempt_time;	/* preemption signal time */
	time_t pre_sus_time;	/* time job ran prior to last suspend */
	uint32_t priority;	/* relative priority of the job,
				 * 0=held, 1=required nodes DOWN/DRAINED */
	uint32_t profile;	/* Level of acct_gather_profile {all | none} */
	char *qos;		/* Quality of Service */
	uint8_t reboot;		/* node reboot requested before start */
	char *req_nodes;	/* comma separated list of required nodes */
	int32_t *req_node_inx;	/* required list index pairs into node_table:
				 * start_range_1, end_range_1,
				 * start_range_2, .., -1  */
	uint32_t req_switch;    /* Minimum number of switches */
	uint16_t requeue;       /* enable or disable job requeue option */
	time_t resize_time;	/* time of latest size change */
	uint16_t restart_cnt;	/* count of job restarts */
	char *resv_name;	/* reservation name */
	char *sched_nodes;	/* list of nodes scheduled to be used for job */
	dynamic_plugin_data_t *select_jobinfo; /* opaque data type,
						* process using
						* slurm_get_select_jobinfo()
						*/
	uint16_t shared;	/* 1 if job can share nodes with other jobs */
	uint16_t show_flags;	/* conveys level of details requested */
	uint16_t sockets_per_board;/* sockets per board required by job */
	uint16_t sockets_per_node; /* sockets per node required by job  */
	time_t start_time;	/* time execution begins, actual or expected */
	uint16_t start_protocol_ver; /* Slurm version step was started with
				      *	either srun or the lowest slurmd version
				      *	it is talking to */
	char *state_desc;	/* optional details for state_reason */
	uint16_t state_reason;	/* reason job still pending or failed, see
				 * slurm.h:enum job_state_reason */
	char *std_err;		/* pathname of job's stderr file */
	char *std_in;		/* pathname of job's stdin file */
	char *std_out;		/* pathname of job's stdout file */
	time_t submit_time;	/* time of job submission */
	time_t suspend_time;	/* time job last suspended or resumed */
	char *system_comment;	/* slurmctld's arbitrary comment */
	uint32_t time_limit;	/* maximum run time in minutes or INFINITE */
	uint32_t time_min;	/* minimum run time in minutes or INFINITE */
	uint16_t threads_per_core; /* threads per core required by job  */
	char *tres_bind;	/* Task to TRES binding directives */
	char *tres_freq;	/* TRES frequency directives */
	char *tres_per_job;	/* semicolon delimited list of TRES=# values */
	char *tres_per_node;	/* semicolon delimited list of TRES=# values */
	char *tres_per_socket;	/* semicolon delimited list of TRES=# values */
	char *tres_per_task;	/* semicolon delimited list of TRES=# values */
	char *tres_req_str;	/* tres reqeusted in the job */
	char *tres_alloc_str;   /* tres used in the job */
	uint32_t user_id;	/* user the job runs as */
	char *user_name;	/* user_name or null. not always set, but
				 * accurate if set (and can avoid a local
				 * lookup call) */
	uint32_t wait4switch;   /* Maximum time to wait for minimum switches */
	char *wckey;            /* wckey for job */
	char *work_dir;		/* pathname of working directory */
} slurm_job_info_t;
#endif

namespace {
  std::string state_to_state_description[] = {
	"PENDING (queued waiting for initiation)",
	"RUNNING (allocated resources and executing)",
	"SUSPENDED (allocated resources, execution suspended)",
	"COMPLETE (completed execution successfully) ",
	"CANCELLED (cancelled by user) ",
	"FAILED (completed execution unsuccessfully) ",
	"TIMEOUT (terminated on reaching time limit) ",
	"NODE_FAIL (terminated on node failure) ",
	"PREEMPTED (terminated due to preemption) ",
	"BOOT_FAIL (terminated due to node boot failure) ",
	"DEADLINE (terminated on deadline) ",
	"OOM (experienced out of memory error) "
  };
}

JobInfo::JobInfo( slurm_job_info_t* _info ) {
  if ( _info == nullptr ) {
    throw "error info pointer is null";
  }
  info = _info; 
}

std::string JobInfo::get_description(){
  if ( info->name == nullptr ) {
    return "no job description avalilable";
  }
  return info->name;
}

uint32_t JobInfo::get_id() {
  return info->job_id;
}

std::string JobInfo::get_user_name() {
  // TODO user name is not set in this case and 
  // has to be infered from the system
  if ( info->user_name == nullptr ) {
    string uid = to_string(info->user_id);
    return "null("s + uid + ")";
  }
  return info->user_name;
}

std::string JobInfo::get_state() {
  return state_to_state_description[info->job_state];
}

std::string JobInfo::get_node_list() {
  if ( info->nodes == nullptr ) {
    return "no node info available";
  }
  return info->nodes; 
}










