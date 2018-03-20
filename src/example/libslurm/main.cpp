#include <slurm/slurm.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char** argv){
		time_t time;
		slurm_get_end_time(14090, &time);
		
 		printf("%s", asctime(gmtime(&time)));

    return 0;
}
