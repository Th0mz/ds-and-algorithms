CC      = gcc
TFLAG   = -DTEST_ARRAY
RM      = rm -f

default: clean all

all: Array

Array: array.c ../element-type.c
	$(CC) $(TFLAG) array.c ../element-type.c -o array; ./array

clean veryclean:
	$(RM) array
