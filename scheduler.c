/*
 * COMP 3500: Project 5 Scheduling
 * Xiao Qin
 * Version 1.0  11/18/2019
 *
 * This source code shows how to conduct separate compilation.
 *
 * How to compile using Makefile?
 * $make
 *
 * How to manually compile?
 * $gcc -c open.c
 * $gcc -c read.c
 * $gcc -c print.c
 * $gcc open.o read.o print.o scheduler.c -o scheduler
 *
 * How to run?
 * Case 1: no argument. Sample usage is printed
 * $./scheduler
 * Usage: scheduler <file_name>
 *
 * Case 2: file doesn't exist.
 * $./scheduler file1
 * File "file1" doesn't exist. Please try again...
 *
 * Case 3: Input file
 * $./scheduler task.list
 * data in task.list is printed below...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "print.h"
#include "open.h"
#include "read.h"
#include "user_input.h"
#include "fcfs_policy.h"

int main( int argc, char *argv[] )  {
   
    //  scheduler should only 'route' the task array with the policy choice to the correct policy


    // char *file_name; /* file name from the commandline */
    FILE *fp; /* file descriptor */
    task_t task_array[MAX_TASK_NUM]; // defines task_array
    user_input_t choice; // defines user_input struct
    int task_count = 0;

    //  int error_code;
    // u_int i;
    // u_int count;

    if (argc < 3 || argc > 4) {
        printf("Incorrect format.\n");
        printf("Correct Input: <file_name> Choose a policy: [FCFS | RR |SRTF] Enter a time quantum if choosing RR: [time quantum]\n");
        return EXIT_FAILURE;
    }

    if(cmd_line_parser(argc, argv, &choice) != 0) {
        return EXIT_FAILURE;
    }

    if (open_file(choice.file_name, &fp) != 0) {
        printf("Error opening file: %s\n", choice.file_name);
        return EXIT_FAILURE;
    }

    read_file(fp, task_array, &task_count);
    fclose(fp);
    // error_code = open_file(argv[1], &fp);
    // if (error_code == 1)
    //     return EXIT_FAILURE;


    // //testing
    // char test_input[] = "task.list FCFS"; 
    // if(cmd_line_parser(test_input, &choice) != 0) {
    //     return EXIT_FAILURE;
    // }

    // if(open_file(choice.file_name, &fp) != 0) {
    //     return EXIT_FAILURE;
    // }

    // read_file(fp, task_array, &task_count);
    // fclose(fp);

    // TESTING: Ensure data is stored and passed properly

    printf("\n=============================================\n");
    printf("[TEST] 1. VERIFYING PARSER OUTPUT (user_input_t)\n");
    printf("=============================================\n");
    printf("Stored Filename: %s\n", choice.file_name);
    printf("Stored Policy  : %s\n", choice.policy);
    printf("Stored Quantum : %d\n", choice.quantum);

    printf("\n=============================================\n");
    printf("[TEST] 2. VERIFYING READ OUTPUT (task_array)\n");
    printf("=============================================\n");
    printf("Total Tasks Successfully Loaded: %d\n", task_count);
    
    for (int i = 0; i < task_count; i++) {
        printf("Task [%d] -> PID: %u | Arrival: %u | Burst: %u\n", 
               i, task_array[i].pid, task_array[i].arrival_time, task_array[i].burst_time);
    }
    printf("=============================================\n\n");
    // =================================================================



    

    // read_file(fp, task_array, &count);
    // print_task_list(task_array, count);

    // fcfs_policy(task_array, count);

    // fclose(fp);
    return EXIT_SUCCESS;
}
