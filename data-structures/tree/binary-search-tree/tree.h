#ifndef TREE
#define TREE

#include <stdbool.h>
#include <math.h>
#include "../../element-type.h"
#include "../../queue/queue.h"

// auxiliary maximum function
#define max(x,y) (((x) >= (y)) ? (x) : (y))

/* Data Structure */
typedef struct node_t {
    Pointer value;
    struct node_t *left, *right;
} node_t;

typedef node_t* Node;

typedef struct tree_t {
    Node root;
    uint64_t size;
    ElementType elem_t;
} tree_t;

typedef tree_t* Tree;

/* Built-in Functions */
Tree bst_create (ElementType T);
int bst_get_depth(Tree T);
void bst_insert (Tree T, Pointer value);
bool bst_search (Tree T, Pointer value);
bool bst_delete (Tree T, Pointer value);

void print (Tree T);
void destroy (Tree T);

#endif
