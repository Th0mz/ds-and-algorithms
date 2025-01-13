CC      = gcc
TFLAG   = -DTEST_LINKED_LIST
RM      = rm -f

default: clean all

all: LinkedList

LinkedList: linked-list.c ../../element-type.c
	$(CC) $(TFLAG) linked-list.c ../../element-type.c -o linked-list; ./linked-list

clean veryclean:
	$(RM) linked-list
