#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>
#include "../../element-type.h"

/* Data Structure */
typedef struct list_node_t {
    Pointer value;
    struct list_node_t* next;
} list_node_t;

typedef list_node_t* ListNode;

typedef struct list_t {
    ListNode top;
    u_int64_t size;
    ElementType elem_t;
} List_T;

typedef List_T* List;

/* Built-in Functions */
List ll_create (ElementType elem_t);
Pointer ll_access (List L, u_int64_t index);
bool ll_update (List L, Pointer value, u_int64_t index);
int ll_search (List L, Pointer value);
bool ll_insert(List L, Pointer value, u_int64_t index);
bool ll_delete(List L, u_int64_t index);
    
void ll_print(List L);
void ll_destroy(List L);

#endif 

