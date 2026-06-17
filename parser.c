#include <stdio.h> // required for file IO
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define INPUTARGS 16

static struct {
    const char *name;
    int(*func)(int nargs, char **args);
} cmdtable[] = {
    {"FCFS",    fcfs_policy},
    {"RR",      rr_policy},
    {"SRTF",    srtf_policy},
    {NULL,      NULL}
};

int cmd__line_parser(char *cmd){
    time_t beforeMS, afterMS, millis;
    uint32_t beforeMsec, afterMsec, msecs;
    char *args[INPUTARGS]; // array of string pointers, each entry = word
    int nargs = 0;  // counter tracks how many valid values in inputArgs
    char *word;
    char *context;
    int i, result;

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

    for (i = 0; cmdtable[i].name; i++) {
        if(*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
            assert(cmdtable[i].func != NULL);

            gettime(&beforeMS, &beforeMsec);

            result = cmdtable[i].func(nargs, args);

            gettime(&afterMS, &afterMsec);

            getinterval(beforeMsec, beforeMS, afterMsec, afterMS, &millis, &msecs);

            printf("Operation took %lu.%09lu milliseconds\n",
                    (unsigned long) millis,
                    (unsigned long) msecs);

                return result;

        }
    }

    printf("%s: Command not found\n", args[0]);
    return EINVAL;

    }