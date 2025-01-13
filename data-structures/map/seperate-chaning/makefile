CC      = gcc
TFLAG   = -DTEST_MAP
RM      = rm -f

default: clean all

all: Map

Map: map.c ../../element-type.c
	$(CC) $(TFLAG) map.c ../../element-type.c -o map; ./map

clean veryclean:
	$(RM) map
