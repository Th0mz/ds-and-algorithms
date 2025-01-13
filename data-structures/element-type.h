#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Pointer;
typedef int (*CompareFunc)(Pointer a, Pointer b);
typedef void(*PrintFunc)(Pointer elem);
typedef void(*DestroyFunc)(Pointer value);
typedef Pointer(*CreateFunc)(Pointer value);
typedef u_int64_t (*HashFunc)(Pointer value);


typedef struct elem_t {
    /* element info */
    size_t size;          // element size

    /* element manipulation functions */
    CreateFunc create;    // create element
    CompareFunc compare;  // compare elements
    PrintFunc print;      // print element
    DestroyFunc destroy;  // destroy element
    HashFunc hash;        // hash element
} ElementType;

/* concrete integer type */
const ElementType int_t;

/* concrete character type */
const ElementType char_t;

/* concrete string type */
const ElementType str_t;

/* concrete pointer type */
const ElementType ptr_t;


#endif