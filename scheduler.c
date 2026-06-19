#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "print.h"
#include "open.h"
#include "read.h"
#include "user_input.h"
#include "fcfs_policy.h"
#include "rr_policy.h"
#include "srtf_policy.h"

int main( int argc, char *argv[] )  {
   
    // Print file name
    printf("The file name is: %s\n", argv[1]);

    //Print policy
    printf("The chosen policy is: %s\n", argv[2]);
    
    // Print basic instructions 
    printf("Usage: scheduler task_list_file [FCFS|RR|SRTF] [time_quantum]\n");
    
    // Handles the RR policy and ensures the correct args are entered 
    if (argc >= 3 && strcmp(argv[2], "RR") == 0) {
        if (argc == 4){
            printf("time_quantum is set to %s\n", argv[3]);
        } else {
            printf("Please enter time_quantum for the RR policy!\n");
            return EXIT_FAILURE;
        }
    }

    FILE *fp; /* file descriptor */
    task_t task_array[MAX_TASK_NUM]; // defines task_array
    user_input_t choice; // defines user_input struct
    int task_count = 0;

    if (argc < 3 || argc > 4) { // checks for the correct number of args
        printf("Incorrect format.\n");
        printf("Correct Input: <file_name> Choose a policy: [FCFS | RR |SRTF] Enter a time quantum if choosing RR: [time quantum]\n");
        return EXIT_FAILURE;
    }

    if(cmd_line_parser(argc, argv, &choice) != 0) { // one of the args has failed
        return EXIT_FAILURE;
    }

    if (open_file(choice.file_name, &fp) != 0) {
        printf("Error opening file: %s\n", choice.file_name);
        return EXIT_FAILURE;
    }

    read_file(fp, task_array, &task_count);
    fclose(fp);

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
