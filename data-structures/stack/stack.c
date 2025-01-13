#include "stack.h"

/* Built-in Functions */
Stack stk_create (ElementType elem_t) {
    Stack stack = malloc(sizeof(_stack_t));
    assert(stack != NULL);

    stack->top = NULL;
    stack->size = 0;
    stack->elem_t = elem_t;

    return stack;
}

Pointer stk_top (Stack S) {
    assert(S != NULL);
    return S->top->value;
}

void stk_push(Stack S, Pointer value) {
    assert(S != NULL);
    ElementType T = S->elem_t;

    StackNode new_head = malloc(sizeof(stack_node_t));
    assert(new_head != NULL);

    new_head->value = T.create(value);
    new_head->next = S->top;
    S->top = new_head;

    S->size++;
}

Pointer stk_pop(Stack S) {
    assert(S != NULL);
    if (S->top == NULL) {
        return NULL;
    }

    StackNode old_head = S->top;
    Pointer value = S->top->value;
    S->top = S->top->next;

    free(old_head);
    S->size--;
    return value;
}

void stk_print(Stack S) {
    assert(S != NULL);
    ElementType T = S->elem_t;

    for (StackNode node = S->top; node != NULL; node = node->next) {
        T.print(node->value);
        printf(" ");
    }

    printf("\n");
}

void stk_destroy(Stack S) {
    assert(S != NULL);
    ElementType T = S->elem_t;

    StackNode node = S->top;
    while (node != NULL) {
        StackNode tmp = node;
        node = node->next;

        T.destroy(tmp->value);
        free(tmp);
    }
}

#ifdef TEST_STACK

int main () {
    ElementType T = int_t;
    Stack stack = stk_create(int_t);

    for (int i = 1; i < 5; i++) {
        stk_push(stack, &i);
        printf("push '%d' into the stack\n", i);
    }

    printf("stack : ");
    stk_print(stack);

    for (int i = 0; i < 5; i++) {
        Pointer elem = stk_pop(stack);
        printf("pop '");
        T.print(elem);
        printf("' from the stack\n");
        
        T.destroy(elem);
    }

    printf("stack : ");
    stk_print(stack);
    stk_destroy(stack);
    return 0;
}

#endif

