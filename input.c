/*
 * COMP 3500: Project 5 Scheduling
 * Xiao Qin
 * Version 1.2  11/14/2019
 *
 * This source code shows how to pass commandline arguments to your progrm
 *
 * How to compile? 
 * $gcc input.c -o command
 *
 * How to run?
 * Case 1: no argument. Sample usage is printed
 * $./input
 * Usage: input <file_name> 
 *
 * Case 2: file doesn't exist. 
 * $./input file1 
 * File "file1" doesn't exist. Please try again... 
 *
 * Case 3: Input file
 * $./input task.list
 * data in task.list is printed below...
 */
#include <stdio.h> // required for file IO
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_NUM 32

typedef unsigned int u_int;

typedef struct task {
    u_int pid;
    u_int arrival_time;
    u_int burst_time;
} task_t;

int main( int argc, char *argv[] )  { 
    char *file_name; /* file name from the commandline */
    FILE *fp; /* file descriptor */
    task_t task_array[MAX_TASK_NUM]; 
    
    u_int i;
    u_int count;

    if (argc != 2) {
        printf("Usage: input <file_name>\n");
        return EXIT_FAILURE;
    }
    
    file_name = argv[1];
    if (! (fp = fopen(file_name, "r"))) {
        printf("File %s can't be opened. Please retry ...\n");
        return EXIT_FAILURE;
    }

    printf("Open file: %s\n", file_name); // if this line is reached, the file has been successfully opened ---- 

    /* read data from input file */
    count = 0;
    while (fscanf(fp, "%u %u %u", &task_array[count].pid, &task_array[count].arrival_time, \ 
                  &task_array[count].burst_time)!= EOF) {
        count++;
    }
 
    printf("There are %u tasks loaded from %s ...\n", count, file_name);

    /* print task_array to check input file */
    for (i = 0; i < count; i++)
        printf("Task PID: %u, Arrival Time: %u, Burst Time: %u\n", task_array[i].pid, \
               task_array[i].arrival_time, task_array[i].burst_time);

    printf("Press any key to continue ...\n");
    getchar();

    fclose(fp);
    return EXIT_SUCCESS;
}

/* module 1 - 'import or data load'- first function should load files from the tasklist and turn an external entity into an internal one
this should be stored in d1.  The simulator can access only internal files.  

- task list has 3 ints - pid, arrival_time, and cpu-time - called burst time in task struct in THIS file. 

- the prgm takes an argument from a user from the CLI -  a file name

- argc above tells your exe how many arguments the user has entered - one of the args is the name of your exe so argc will always have a min count of 1. It is the first arg
- argV is argument vector and is a 2D array - the first dimension holds all the args as pointers and the second dimension holds each token.  So argv0 points to the scheduler.exe, argv1 might point to the task list.  This is in the main function above so the program enters here.  

- file descriptor - FILE *fp above - functions as a file ID. This is a pointer so its a dynamically created ID. A pointer is used bc the memory that holds the file descriptor will be dynamically created by the memory manager.  If the mem mgr doesnt have the mem to allocate to you, fp will be NULL - always check for this. 
    - in userland, all we see is a file name.  However the file system uses the descriptor under the hood, file systems and 'the machine' generally doesnt want to process strings, they want a unique file to be represented in a way they can understand efficiently
    - when a user wants to access a file by typing in the file name, the file name has to be converted to the descriptor so the file system can understand it
    - this translation is done by fopen(file_name, "r"); above.  'r' means when this file opens, it is read-only. 'rw' can also be used to edit immediately
    - fopen returns fp - once the conversion has been made, you can no longer use the string file_name, you need to use the file descriptor to issue open / close, read / write commands, etc

- scanf is used to capture input from the keyboard.  fscanf, allows you to read in a files contents.  To the system these two functions do the same thing -> data is coming from outside the system.
    - fscanf treats a file as a keyboard but with continuous, automatic input. A major difference between scanf and fscanf is that scanf's file descriptor is the keyboard so no fp is required.  fscanf needs a file descriptor. 
    - fscanf(fp, %u, %u, %u) - file desriptor that is returned from fopen, tasklist is simply 3 unsigned ints, hence %u as the format specifier - id, arr_time, cpu_time respectively
    - next args - &task_array[count].pid, .arr_time, .burst_time are then stored in the task_array which is d1 - the internally stored version of the file
    - != EOF (while the end of the file hasnt been reached) - EOF is recognized by linux systems
    - internally, the initial pointer to this array is managed by the file descriptor - everytime you call fscanf in the while loop, the internal pointer moves one step forward. EOF points to the first 'empty line' at the end of the file, indicating you have reached the end
    - printf inside the for loop to write results to the console
    - ** do not forget fclose to close the channel to the file!  otherwise unexpected behaviors are expected

- most linux file systems, especially with formatted data, can be accessed this way.  This is worth internalizing for future needs, especially when dealing with file systsm, OS, linux, etc.  
- 
*/
