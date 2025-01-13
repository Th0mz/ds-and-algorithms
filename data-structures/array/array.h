#ifndef ARRAY
#define ARRAY

#include <stdbool.h>
#include "../element-type.h"

/* Data Structure */
typedef struct array_t {
    Pointer fst;
    u_int64_t size;
    ElementType elem_t;
} array_t;

typedef array_t* Array;

/* Built-in Functions */
Array arr_create (ElementType elem_t, u_int64_t size);
Pointer arr_access (Array A, u_int64_t index);
bool arr_update (Array A, Pointer value, u_int64_t index);
int arr_search (Array A, Pointer value);
bool arr_insert (Array A, Pointer value, u_int64_t index);
bool arr_delete (Array A, u_int64_t index);

void print(Array A);
void destroy (Array A);

#endif