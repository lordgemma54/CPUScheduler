#include <stdio.h>
#include "fcfs_policy.h"

// clock = 0;
// int ready_queue[];
// int finished_tasks[];

void fcfs_policy(task_t task_list[], int size) {
    for(int i = 0; i < size; i++) {
        printf("index %d: PID: %u, Arrival: %u, Burst: %u\n",
        i,
        task_list[i].pid,
        task_list[i].arrival_time,
        task_list[i].burst_time);
    }
    // ready_queue[] = task_list;
    printf("Helooooo");

    // while(ready_queue != NULL) {
    //     printf("PID: %d, Arrival: %u, Burst: %u", task_list.pid, 
    //         task_list.arrival_time, task_list.burst_time );

        
    //     clock++;
    // }

}