#include <stdio.h> // required for file IO
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>

#include "user_input.h"
#include "fcfs_policy.h"
#include "rr_policy.h"
#include "srtf_policy.h"

#define INPUTARGS 16

int cmd_line_parser(int argc, char *argv[], user_input_t *inputs){

        inputs->file_name = argv[1]; // stores second arg as file name
        inputs->policy = argv[2]; // stores policy choice

        if(strcmp(inputs->policy, "FCFS") != 0 &&
           strcmp(inputs->policy, "RR") != 0 &&
           strcmp(inputs->policy, "SRTF") != 0) {
                printf("Error: No such scheduling policy '%s'. Use FCFS, RR, or SRTF. \n", inputs->policy);
                return EINVAL;
            }

        if(strcmp(inputs->policy, "RR") == 0) { // ensures theres an arg for time quantum
            if(argc < 4) {
                printf("Error: Round Robin policy requires a time quantum.\n");
                return EINVAL;
            }
            inputs->quantum = atoi(argv[3]); // converts ascii to integer 
            if(inputs->quantum <=0) {
                printf("Error: Time quantum must be a positive integer.\n");
                return EINVAL;
            }
        } else {
            inputs->quantum = 0;
        }
        return 0;
    }
    