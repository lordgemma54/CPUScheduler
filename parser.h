#ifndef PARSER_H
#define PARSER_H

#include "scheduler.h"   // Provides task_t and MAX_TASK_NUM
#include "user_input.h"  // Provides user_input_t

// Parses command line arguments, opens files, and populates the data arrays
int cmd_line_parser(int argc, char *argv[], user_input_t *choice, task_t *task_array, int *task_count);

#endif

/*
 * COMP 3500: Project 5 Scheduling
 * Rahul Venkatesh
 * 6/19/2026
 */