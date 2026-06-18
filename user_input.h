#ifndef USER_INPUT
#define USER_INPUT

typedef struct input {
    char *file_name;
    const char *policy;
    int quantum;
}user_input_t;

int cmd_line_parser(int argc, char *argv[], user_input_t *inputs);

#endif