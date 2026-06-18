#include <stdio.h>
#include "fcfs_policy.h"



void fcfs_policy(task_t task_list[], int size) {
int clock = 0;

task_t ready_queue[MAX_TASK_NUM];
int ready_count = 0;

task_t finished_tasks[MAX_TASK_NUM];
int finish_count = 0;

// testing
    // for(int i = 0; i < size; i++) {
    //     printf("index %d: PID: %u, Arrival: %u, Burst: %u\n",
    //     i,
    //     task_list[i].pid,
    //     task_list[i].arrival_time,
    //     task_list[i].burst_time);
    // }
    
    printf("Helooooo\n");

    // while(ready_queue != NULL) {
    //     printf("PID: %d, Arrival: %u, Burst: %u", task_list.pid, 
    //         task_list.arrival_time, task_list.burst_time );

        
    //     clock++;
    // }

}