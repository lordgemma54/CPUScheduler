#include <stdio.h>
#include "fcfs_policy.h"
#include "stat_info.h"


void fcfs_policy(task_t task_list[], int size) {
    int clock = 0;

    task_t ready_queue[MAX_TASK_NUM];
    int ready_count = 0;

    task_t finished_tasks[MAX_TASK_NUM];
    int finish_count = 0;

    // printf("%d tasks were loaded from \"%s\". Press Enter to continue...\n", size, file_name);
    
    // getchar();

    while(finish_count < size) { //preps ready queue
        for (int i = 0; i < size; i++) {
            if(task_list[i].arrival_time == clock) {
                ready_queue[ready_count] = task_list[i];
                ready_queue[ready_count].remaining_time = task_list[i].burst_time;
                ready_queue[ready_count].start_time = -1;
                ready_count++;
            }
        }

        
            if(ready_count > 0) { // there is a process in the queue
                if(ready_queue[0].start_time == -1) {
                    ready_queue[0].start_time = clock;
                    ready_queue[0].response_time = clock - ready_queue[0].arrival_time;
                }
        
                ready_queue[0].remaining_time--;
                printf("<time %d> process %d is running\n", clock, ready_queue[0].pid);
        
                if(ready_queue[0].remaining_time == 0) {
                    ready_queue[0].finish_time = clock + 1;
        
                    finished_tasks[finish_count++] = ready_queue[0];
                    
                    printf("<time %d> process %d is finished...\n", ready_queue[0].finish_time, ready_queue[0].pid);
        
                    for(int j = 0; j < ready_count - 1; j++){
                        ready_queue[j] = ready_queue[j + 1]; // moves queued tasks forward 1
                    }
                    ready_count--;
                }


            } else {
                printf("Time %d: idle\n", clock);
            }
            clock++;
    }

    compute_stats(finished_tasks, finish_count, clock);

//testing
/*
    for(int k = 0; k < finish_count; k++) {
        printf("PID: %u, Arrival: %u, Burst: %u, Response: %d, Start: %d, Finish: %d\n",
        finished_tasks[k].pid,
        finished_tasks[k].arrival_time,
        finished_tasks[k].burst_time,
        finished_tasks[k].response_time,
        finished_tasks[k].start_time,
        finished_tasks[k].finish_time);
    }
    printf("Helooooo\n");
    */

}