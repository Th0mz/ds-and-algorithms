#ifndef QUEUE
#define QUEUE


#include <stdbool.h>
#include "../element-type.h"

/* Data Structure */
typedef struct queue_node_t {
    Pointer value;
    struct queue_node_t* next;
} queue_node_t;

typedef queue_node_t* QueueNode;

typedef struct queue_t {
    QueueNode head;
    QueueNode tail;
    u_int64_t size;
    ElementType elem_t;
} queue_t;

typedef queue_t* Queue;

/* Built-in Functions */
Queue q_create (ElementType elem_t);
Pointer q_front (Queue Q);
Pointer q_rear (Queue Q);
bool q_is_empty (Queue Q);
void q_enqueue(Queue Q, Pointer value);
Pointer q_dequeue(Queue Q);

void q_print(Queue Q);
void q_destroy(Queue Q);

#endif