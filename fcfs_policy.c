#include <stdio.h>
#include "fcfs_policy.h"

void fcfs_policy(task_t task_list[], int size) {
    for(int i = 0; i < size; i++) {
        printf("index %d: PID: %u, Arrival: %u, Burst%u\n",
        i,
        task_list[i].pid,
        task_list[i].arrival_time,
        task_list[i].burst_time);
    }
}