#include <stdio.h>
#include "stat_info.h"


void compute_stats(task_t finished_tasks[], int finish_count, int clock){  // avg wait time
    int wait_time_sum = 0;
    int turnaround_time = 0;
    int turnaround_time_sum = 0;
    int response_time_sum = 0;
    int burst_time_sum = 0;


    for(int i = 0; i < finish_count; i++) {
        turnaround_time = finished_tasks[i].finish_time - finished_tasks[i].arrival_time;
        turnaround_time_sum += turnaround_time;
        
        wait_time_sum += turnaround_time - finished_tasks[i].burst_time;
        response_time_sum += finished_tasks[i].response_time;
        burst_time_sum += finished_tasks[i].burst_time;
    }

// ------------------------------------------------------------
    // Calculate avgs
    double cpu_usage = 0.0;
    double avg_wait_time = (double)wait_time_sum / finish_count;
    double avg_response_time = (double)response_time_sum / finish_count;
    double avg_turnaround_time = (double) turnaround_time_sum / finish_count;
    if (clock > 0) {
        cpu_usage = ((double)burst_time_sum / clock) * 100;
    } else {
        cpu_usage = 0.0;
    }
// ------------------------------------------------------------
    // Print
    printf("*******************************************************\n");
    printf("Average wait time: %.2f\n", avg_wait_time); 
    printf("Average response time: %.2f\n", avg_response_time); 
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);
    printf("Overall CPU usage: %.2f%%\n", cpu_usage);
    printf("*******************************************************\n");
}












// time_t beforeMS, afterMS, millis;
//     uint32_t beforeMsec, afterMsec, msecs;

            // gettime(&beforeMS, &beforeMsec);

            // result = cmdtable[i].func(nargs, args);

            // gettime(&afterMS, &afterMsec);

            // getinterval(beforeMsec, beforeMS, afterMsec, afterMS, &millis, &msecs);

            // printf("Operation took %lu.%09lu milliseconds\n",
            //         (unsigned long) millis,
            //         (unsigned long) msecs);

            //     return result;