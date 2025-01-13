#ifndef STACK
#define STACK

#include <stdbool.h>
#include "../element-type.h"

/* Data Structure */
typedef struct stack_node_t {
    Pointer value;
    struct stack_node_t* next;
} stack_node_t;

typedef stack_node_t* StackNode;

typedef struct _stack_t {
    StackNode top;
    u_int64_t size;
    ElementType elem_t;
} _stack_t;

typedef _stack_t* Stack;

/* Built-in Functions */
#include "stack.h"

/* Built-in Functions */
Stack stk_create (ElementType elem_t);
Pointer stk_top (Stack S);
void stk_push(Stack S, Pointer value);
Pointer stk_pop(Stack S);

void stk_print(Stack S);
void stk_destroy(Stack S);

#endif