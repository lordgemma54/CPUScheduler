#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "open.h"
#include "read.h"
#include "user_input.h"
#include "fcfs_policy.h"
#include "rr_policy.h"
#include "srtf_policy.h"
#include "parser.h"

int main( int argc, char *argv[] )  {


    // Memory allocated here on the stack
    user_input_t choice; // defines user_input struct
    task_t task_array[MAX_TASK_NUM]; // defines task_array
    int task_count = 0;

    // Send pointers down to parser.c to be populated
    if (cmd_line_parser(argc, argv, &choice, task_array, &task_count) != 0) {
        return EXIT_FAILURE;
    }

// the policy requested by the user is routed to the corresponding function
    if(strcmp(choice.policy, "FCFS") == 0) {
        fcfs_policy(task_array, task_count);
    }

    if(strcmp(choice.policy, "RR") == 0) {
        rr_policy(task_array, task_count, choice.quantum);
    }

     if(strcmp(choice.policy, "SRTF") == 0) {
        srtf_policy(task_array, task_count);
    }
    return EXIT_SUCCESS;

/*
 * COMP 3500: Project 5 Scheduling
 * Rahul Venkatesh
 * 6/19/2026
 */
}
