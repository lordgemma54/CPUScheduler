#ifndef USER_INPUT
#define USER_INPUT

typedef struct input {
    const char *file_name;
    const char *policy;
    int quantum;
}user_input_t;

void capture_input(const user_input_t *inputs);

#endif