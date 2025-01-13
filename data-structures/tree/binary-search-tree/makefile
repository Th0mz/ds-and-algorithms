CC      = gcc
TFLAG   = -DTEST_TREE
RM      = rm -f

default: clean all

all: Tree

Tree: tree.c ../../element-type.c ../../queue/queue.c
	$(CC) $(TFLAG) tree.c ../../element-type.c ../../queue/queue.c -o tree; ./tree

clean veryclean:
	$(RM) tree
