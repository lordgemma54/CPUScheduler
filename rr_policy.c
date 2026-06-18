#include <stdio.h>
#include "rr_policy.h"

void rr_policy(task_t task_list[], int size, int quantum) {
    for(int i = 0; i < size; i++) {
        printf("index &d: %d\n", i,task_list[i]);
    }
}