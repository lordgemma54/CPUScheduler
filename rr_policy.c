#include <stdio.h>
#include "rr_policy.h"
#include "stat_info.h"

void rr_policy(task_t task_list[], int size, int quantum) {
    int clock = 0;
    int quantum_clock = 0; // to preempt the process after the time quantum has elapsed

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
            if(ready_queue[0].start_time == -1) { 
                ready_queue[0].start_time = clock;
                ready_queue[0].response_time = clock - ready_queue[0].arrival_time;
            } 

            ready_queue[0].remaining_time--;
            quantum_clock++; // one cycle closer to being preempted

            printf("<time %d> process %d is running\n", clock, ready_queue[0].pid);

            if(ready_queue[0].remaining_time == 0) { // this if block is if the process finishes
                ready_queue[0].finish_time = clock + 1;
                printf("<time %d> process %d is finished...\n", ready_queue[0].finish_time, ready_queue[0].pid);

                finished_tasks[finish_count++] = ready_queue[0];
                
                for(int j = 0; j <= ready_count - 1; j++){
                    ready_queue[j] = ready_queue[j + 1]; // moves queued tasks forward so the head of the queue is never empty
                }

                ready_count--;
                quantum_clock = 0;

            } else if (quantum_clock == quantum) { // this else if block is if the process hasnt finished but its time slot has expired
            task_t preempted_task = ready_queue[0];
            
            for(int j = 0; j <= ready_count - 1; j++){
                    ready_queue[j] = ready_queue[j + 1]; // moves queued tasks forward 1
                }
            
            ready_queue[ready_count - 1] = preempted_task;
            quantum_clock = 0;
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




