#include "linked-list.h"

/* Built-in Functions */
List ll_create (ElementType elem_t) {
    List list = malloc(sizeof(struct list_t));
    assert(list != NULL);

    list->top = NULL;
    list->bottom = NULL;
    list->size = 0;
    list->elem_t = elem_t;

    return list;
}

Pointer ll_access (List L, u_int64_t index) {
    assert(L != NULL);
    if (L->size == 0) {
        return NULL;
    }

    index = index % L->size;
    ListNode node = L->top;
    for (int i = 0; i != index; i++) {
        node = node->next;
    }

    return node->value;
}

bool ll_update (List L, Pointer value, u_int64_t index) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    if (L->size == 0) {
        return false;
    }

    index = index % L->size;
    ListNode node = L->top;
    for (int i = 0; i != index; i++) {
        node = node->next;
    }

    Pointer old_value = node->value;
    node->value = T.create(value);
    T.destroy(old_value);

    return true;
}

int ll_search (List L, Pointer value) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    int i = 0;
    ListNode node = L->top;
    for (; i < L->size; node = node->next, i++) {
        if (T.compare(node->value, value) == 0) {
            return i;
        }
    }
    
    return -1;
}

bool insert_head(List L, Pointer value) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    ListNode new_node = malloc(sizeof(list_node_t));
    new_node->value = T.create(value);

    /* if the list is empty the new node is both the top and the bottom one */
    if (L->top == NULL) {
        L->top = new_node;
        L->bottom = new_node;
        new_node->next = new_node;
    } else {
        new_node->next = L->top;
        L->top = new_node;
        L->bottom->next = L->top;
    }

    L->size++;
    return true;
}

bool ll_insert(List L, Pointer value, u_int64_t index) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    /* check if it is a head insertion */
    if (index == 0 || L->size == 0) {
        return insert_head(L, value);
    }

    index = index % (L->size + 1);
    ListNode prev = L->top;
    for (int i = 0; i != index - 1; i++) {
        assert(prev != NULL);
        prev = prev->next;
    }

    ListNode new_node = malloc(sizeof(list_node_t));
    new_node->value = T.create(value);
    new_node->next = prev->next;
    prev->next = new_node;

    /* update bottom node if new node is added to the bottom */
    if (index == L->size) {
        L->bottom = new_node;
    }

    L->size++;
    return true;
}

bool delete_head(List L) {
    assert(L != NULL);
    ElementType T = L->elem_t;
    ListNode to_delete = L->top;
    
    if (L->size == 1) {
        L->top =  NULL;
        L->bottom = NULL;
    } else {
        L->top = to_delete->next;
        L->bottom->next = L->top;
    }

    /* delete node */
    T.destroy(to_delete->value);
    free(to_delete);

    L->size--;
    return true;
}

bool ll_delete(List L, u_int64_t index) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    if (L->size == 0) {
        return false;
    }

    index = index % L->size;
    /* check if it is a head deletion */
    if (index == 0) {
        return delete_head(L);
    }

    ListNode prev = L->top;
    for (int i = 0; i != index - 1; i++) {
        assert(prev != NULL);
        prev = prev->next;
    }

    ListNode to_delete = prev->next;
    prev->next = to_delete->next;

    /* update bottom node if new node is added to the bottom */
    if (index == L->size - 1) {
        L->bottom = prev;
    }

    /* delete node */
    T.destroy(to_delete->value);
    free(to_delete);

    L->size--;
    return true;
}

void ll_print(List L) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    int i; ListNode node;  
    for (i = 0, node = L->top; i < L->size; i++, node = node->next) {
        T.print(node->value);
        printf(" -> ");
    }

    printf("*\n");
}

void ll_destroy(List L) {
    assert(L != NULL);
    ElementType T = L->elem_t;

    /* free nodes */
    int i = 0;
    ListNode node = L->top;
    while (i < L->size) {
        ListNode to_delete = node;
        node = node->next;

        T.destroy(to_delete->value);
        free(to_delete);
        i++;
    }

    /* free list structure*/
    free(L);
}


int main () {
    List list = ll_create(int_t);
    for (int i = 0; i < 4; i++) {
        ll_insert(list, &(int){i + 1}, i);
    }

    ll_delete(list, 0);

    int search_val = 1;
    printf("value '%d' is on index : %d\n", search_val, ll_search(list, &search_val));
    printf("index 1 has value of "); int_t.print(ll_access(list, 1)); printf("\n");


    ll_update(list, &(int){5}, 1);

    ll_print(list);
    ll_destroy(list);

    return 0;
}

