#include <stdio.h>
#include "fcfs_policy.h"
#include "stat_info.h"

void fcfs_policy(task_t task_list[], int size) {
    int clock = 0;

    task_t ready_queue[MAX_TASK_NUM];
    int ready_count = 0;

    task_t finished_tasks[MAX_TASK_NUM];
    int finish_count = 0;

    while(finish_count < size) { //preps ready queue
        for (int i = 0; i < size; i++) {  // proc only enters the rq when clock = arr_time
            if(task_list[i].arrival_time == clock) { // sets variables in task_t struct
                ready_queue[ready_count] = task_list[i];
                ready_queue[ready_count].remaining_time = task_list[i].burst_time;
                ready_queue[ready_count].start_time = -1;
                ready_count++;
            }
        }

        
            if(ready_count > 0) { // there is a process in the queue
                if(ready_queue[0].start_time == -1) { // -1 used as a flag to indicate that the process hasnt run on the cpu for the first time
                    ready_queue[0].start_time = clock;
                    ready_queue[0].response_time = clock - ready_queue[0].arrival_time;
                }
        
                ready_queue[0].remaining_time--; // simulates execution on the CPU
                printf("<time %d> process %d is running\n", clock, ready_queue[0].pid);
        
                if(ready_queue[0].remaining_time == 0) { // if the process is done, move task to finished_tasks array
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

    compute_stats(finished_tasks, finish_count, clock); // pass finished_tasks to stat_info for processing

/*
 * COMP 3500: Project 5 Scheduling
 * Rahul Venkatesh
 * 6/19/2026
 */
}