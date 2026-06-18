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

// static struct {
//     const char *name;
//     int(*func)(int nargs, char **args);
// } cmdtable[] = {
//     {"FCFS",    fcfs_policy},
//     {"RR",      rr_policy},
//     {"SRTF",    srtf_policy},
//     {NULL,      NULL}
// };

// void capture_input(const user_input_t *inputs) {
//     printf("filename: %s\n", inputs->file_name);
//     printf("policy: %s\n", inputs->policy);
//     printf("quantum: %s\n", inputs ->quantum);
// }

int cmd_line_parser(char *cmd, user_input_t *inputs){
    
    char *args[INPUTARGS]; // array of string pointers, each entry = word
    int nargs = 0;  // counter tracks how many valid values in inputArgs
    char *word;
    char *context;
    // int i, result;

    for (word = strtok_r(cmd, " ", &context);
        word != NULL;
        word = strtok_r(NULL, " ", &context)) 
        {
            if(nargs >= INPUTARGS) {
                printf("Command line has too many words\n");
                return E2BIG;
            }
            args[nargs++] = word;
        }
        if (nargs == 0) {
            return 0;
        }

        if (nargs < 2) {
            printf("Error: Missing arguments. Format required: file_name policy [quantum]\n");
            return EINVAL;
        }
        inputs->file_name = args[0];
        inputs->policy = args[1];

        if(strcmp(inputs->policy, "RR") == 0) {
            if(nargs <3) {
                printf("Error: Round Robin policy requires a quantum.\n");
                return EINVAL;
                inputs->quantum = atoi(args[2]);
            }
        } else {
            inputs->quantum = 0;
        }
        return 0;
    }
    // for (i = 0; cmdtable[i].name; i++) {
    //     if(*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
    //         assert(cmdtable[i].func != NULL);

            // gettime(&beforeMS, &beforeMsec);

            // result = cmdtable[i].func(nargs, args);

            // gettime(&afterMS, &afterMsec);

            // getinterval(beforeMsec, beforeMS, afterMsec, afterMS, &millis, &msecs);

            // printf("Operation took %lu.%09lu milliseconds\n",
            //         (unsigned long) millis,
            //         (unsigned long) msecs);

                // return result;

        // }


   

    
// =====================================================================
// TESTING: Temporarily included for debugginf purposes
// =====================================================================
// int main(void) {
//     char test_input1[] = "FCFS task.list 10";
//     char test_input2[] = "INVALID_COMMAND";

//     printf("--- Testing Valid Command ---\n");
//     cmd__line_parser(test_input1);

//     printf("\n--- Testing Invalid Command ---\n");
//     cmd__line_parser(test_input2);

//     return 0;
// }