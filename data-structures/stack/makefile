CC      = gcc
TFLAG   = -DTEST_STACK
RM      = rm -f

default: clean all

all: Stack

Stack: stack.c ../element-type.c
	$(CC) $(TFLAG) stack.c ../element-type.c -o stack; ./stack

clean veryclean:
	$(RM) stack
