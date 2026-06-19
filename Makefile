#see README for a manual compilation process
CC = gcc
CFLAGS = -g
OBJ = open.o read.o print.o parser.o fcfs_policy.o stat_info.o
all: test

test: $(OBJ) scheduler.c
	@echo "Creating the scheduler ..."
	$(CC) -o $@ $^ $(CFLAGS)

# scheduler: $(OBJ) scheduler.c
# 	@echo "Creating the scheduler ..."
# 	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	@echo "Creating object files ..."
	$(CC) -c $< -o $@

clean:
	@echo "Deleting object and binary files ..."
	rm -rvf *.o test 
#test was scheduler
