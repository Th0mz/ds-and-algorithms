#include "queue.h"

/* Built-in Functions */
Queue q_create (ElementType elem_t) {
    Queue queue = malloc(sizeof(queue_t));
    assert(queue != NULL);

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->elem_t = elem_t;

    return queue;
}

Pointer q_front (Queue Q) {
    assert(Q != NULL);
    return Q->head->value;
}

Pointer q_rear (Queue Q) {
    assert(Q != NULL);
    return Q->tail->value;
}

bool q_is_empty (Queue Q) {
    assert(Q != NULL);
    return (Q->head == NULL);
}

void q_enqueue(Queue Q, Pointer value) {
    assert(Q != NULL);
    ElementType T = Q->elem_t;

    QueueNode new_tail = malloc(sizeof(queue_node_t));
    assert(new_tail != NULL);

    new_tail->value = T.create(value);
    new_tail->next = NULL;

    /* check if the queue is currently empty */
    if (q_is_empty(Q)) {
        Q->head = new_tail;
    } else {
        Q->tail->next = new_tail;
    }

    Q->tail = new_tail;
    Q->size++;
}

Pointer q_dequeue(Queue Q) {
    assert(Q != NULL);
    
    if (q_is_empty(Q))
        return NULL;


    QueueNode old_head = Q->head;
    Pointer value = Q->head->value;
    Q->head = Q->head->next;

    if (q_is_empty(Q))
        Q->tail = NULL;
    
    free(old_head);
    Q->size--;

    return value;
}

void q_print(Queue Q) {
    assert(Q != NULL);
    ElementType T = Q->elem_t;

    for (QueueNode node = Q->head; node != NULL; node = node->next) {
        T.print(node->value);
        printf(" ");
    }

    printf("\n");
}

void q_destroy(Queue Q) {
    assert(Q != NULL);
    ElementType T = Q->elem_t;

    QueueNode node = Q->head;
    while (node != NULL) {
        QueueNode tmp = node;
        node = node->next;

        T.destroy(tmp->value);
        free(tmp);
    }
}

#ifdef TEST_QUEUE

int main () {
    ElementType T = int_t;
    Queue queue = q_create(int_t);

    for (int i = 1; i < 5; i++) {
        q_enqueue(queue, &i);
        printf("push '%d' into the queue\n", i);
    }

    printf("queue : ");
    q_print(queue);

    for (int i = 0; i < 5; i++) {
        Pointer elem = q_dequeue(queue);
        printf("pop '");
        T.print(elem);
        printf("' from the queue\n");
        
        T.destroy(elem);
    }

    printf("queue : ");
    q_print(queue);
    q_destroy(queue);
    return 0;
}

#endif

