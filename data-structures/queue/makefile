CC      = gcc
TFLAG   = -DTEST_QUEUE
RM      = rm -f

default: clean all

all: Queue

Queue: queue.c ../element-type.c
	$(CC) $(TFLAG) queue.c ../element-type.c -o queue; ./queue

clean veryclean:
	$(RM) queue
