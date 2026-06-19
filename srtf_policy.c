#include <stdio.h>
#include "srtf_policy.h"
#include "stat_info.h"


void srtf_policy(task_t task_list[], int size) {
    int clock = 0;
    task_t ready_queue[MAX_TASK_NUM];
    int ready_count = 0;

    task_t finished_tasks[MAX_TASK_NUM];
    int finish_count = 0;
    
    while (finish_count < size) { 
        for (int i = 0; i < size; i++) { 
            if(task_list[i].arrival_time == clock) { 
                ready_queue[ready_count] = task_list[i];
                ready_queue[ready_count].remaining_time = task_list[i].burst_time;
                ready_queue[ready_count].start_time = -1;
                ready_count++;
            } 
        }
        
        if(ready_count > 0) { 
            
            // finds the index of the process with the shortest remaining time
            int shortest_job_index = 0;
            task_t first_to_execute; 

            for(int i = 1; i < ready_count; i++) {
                if(ready_queue[i].remaining_time < ready_queue[shortest_job_index].remaining_time) {
                    shortest_job_index = i; 
                }
            }

            // temporarily stores the process with the shortest remaining time
            first_to_execute = ready_queue[shortest_job_index];

            for(int j = shortest_job_index; j > 0; j--){
                ready_queue[j] = ready_queue[j - 1]; 
            }
            
            // moves the task with the shortest remaining time to the front of the queue
            ready_queue[0] = first_to_execute;

            if(ready_queue[0].start_time == -1) { 
                ready_queue[0].start_time = clock;
                ready_queue[0].response_time = clock - ready_queue[0].arrival_time;
            } 

            ready_queue[0].remaining_time--; 
            printf("<time %d> process %d is running\n", clock, ready_queue[0].pid);

            if(ready_queue[0].remaining_time == 0) {
                ready_queue[0].finish_time = clock + 1;
                printf("<time %d> process %d is finished...\n", ready_queue[0].finish_time, ready_queue[0].pid);

                finished_tasks[finish_count++] = ready_queue[0];
                
                for(int j = 0; j <= ready_count - 1; j++){
                    ready_queue[j] = ready_queue[j + 1]; 
                }
                ready_count--;

            } 
        }  else {
            printf("Time %d: idle\n", clock);
        }
    clock++;
    }
   compute_stats(finished_tasks, finish_count, clock);

/*
 * COMP 3500: Project 5 Scheduling
 * Rahul Venkatesh
 * 6/19/2026
 */

}      




