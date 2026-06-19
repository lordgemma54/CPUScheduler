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
        for (int i = 0; i < size; i++) { // processes can only join RQ if equal to clock 
            if(task_list[i].arrival_time == clock) { // initialize values in first process
                ready_queue[ready_count] = task_list[i];
                ready_queue[ready_count].remaining_time = task_list[i].burst_time;
                ready_queue[ready_count].start_time = -1;
                ready_count++;
            } 
        }
        
        if(ready_count > 0) { // there is a process in the queue
            if(ready_queue[0].start_time == -1) { // proc has never executed
                ready_queue[0].start_time = clock;
                ready_queue[0].response_time = clock - ready_queue[0].arrival_time;
            } 

            ready_queue[0].remaining_time--; // simulates the process running
            quantum_clock++; // one cycle closer to being preempted

            printf("<time %d> process %d is running\n", clock, ready_queue[0].pid);

            if(ready_queue[0].remaining_time == 0) {
                ready_queue[0].finish_time = clock + 1;
                printf("<time %d> process %d is finished...\n", ready_queue[0].finish_time, ready_queue[0].pid);

                finished_tasks[finish_count++] = ready_queue[0];
                
                for(int j = 0; j <= ready_count - 1; j++){
                    ready_queue[j] = ready_queue[j + 1]; // moves queued tasks forward 1
                }
                ready_count--;
                quantum_clock = 0;
            } else if (quantum_clock == quantum) {
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
}      




