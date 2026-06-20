#include <stdio.h> // required for file IO
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

#include "scheduler.h"
#include "open.h"
#include "read.h"
#include "user_input.h"
#include "fcfs_policy.h"
#include "rr_policy.h"
#include "srtf_policy.h"

#define INPUTARGS 16

int cmd_line_parser(int argc, char *argv[], user_input_t *choice, task_t *task_array, int *task_count){


    FILE *fp; /* file descriptor */

    if (argc < 3 || argc > 4) { // checks for the correct number of args
        printf("Incorrect format.\n");
        printf("Correct Input: <file_name> Choose a policy: [FCFS | RR |SRTF] Enter a time quantum if choosing RR: [time quantum]\n");
        return EXIT_FAILURE;
    }

    choice->file_name = argv[1]; // stores second arg as file name
    choice->policy = argv[2]; // stores policy choice

    // Print file name
    printf("The file name is: %s\n", choice->file_name);

    //Print policy
    printf("The chosen policy is: %s\n", choice->policy);
    
    // Print basic instructions 
    printf("Usage: scheduler task_list_file [FCFS|RR|SRTF] [time_quantum]\n");
    
    // validates policy name
    if(strcmp(choice->policy, "FCFS") != 0 &&
        strcmp(choice->policy, "RR") != 0 &&
        strcmp(choice->policy, "SRTF") != 0) {
            printf("Error: No such scheduling policy '%s'. Use FCFS, RR, or SRTF. \n", choice->policy);
            return EINVAL;
     }

     // ensures theres an arg for time quantum
    if(strcmp(choice->policy, "RR") == 0) { 
            if(argc < 4) {
                printf("Error: Round Robin policy requires a time quantum.\n");
                return EINVAL;
            }
            choice->quantum = atoi(argv[3]); // converts ascii to integer 
            if(choice->quantum <=0) {
                printf("Error: Time quantum must be a positive integer.\n");
                return EINVAL;
            }
        } else {
            choice->quantum = 0;
        }


    if (open_file(choice->file_name, &fp) != 0) {
        printf("Error opening file: %s\n", choice->file_name);
        return EXIT_FAILURE;
    }

    read_file(fp, task_array, task_count);
    fclose(fp);

    return 0;
    }
    