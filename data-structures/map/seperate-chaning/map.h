#ifndef HASH_MAP
#define HASH_MAP

#include <stdbool.h>
#include "../../element-type.h"

#define hash_func2(PRIME, h1) (PRIME - (h1 % PRIME))

static u_int64_t hash_sizes[] =
    { 2, 3, 5, 11, 17, 29, 67, 131, 263, 509, 1021, 2053, 4093, 8179, 16369, 32749, 65521, 131071, 262147, 524287, 1048573, 2097143,
    4194301, 8388593, 16777213, 33554467, 67108879, 134217757, 268435459, 536870923, 1073741827, 2147483647, 4294967291,
    8589934583, 17179869143, 34359738337, 68719476731, 137438953447, 274877906899, 549755813881, 1099511627689, 2199023255531,
    4398046511093, 8796093022151, 17592186044399, 35184372088777, 70368744177643, 140737488355213, 281474976710597, 562949953421231,
    1125899906842597, 2251799813685119, 4503599627370449, 9007199254740881, 18014398509481951, 36028797018963913, 72057594037927931,
    144115188075855859, 288230376151711717, 576460752303423433, 1152921504606846883, 2305843009213693951, 4611686018427387847 };

const u_int64_t get_size(u_int8_t i) {
    return hash_sizes[i];
}

/* Data Structure */
typedef struct bucket_t {
    Pointer key;
    Pointer value;
    struct bucket_t* next;
} bucket_t;

typedef bucket_t* Bucket;

typedef struct hash_table_t {
    Bucket* buckets;
    u_int8_t capacity;
    u_int64_t elements;

    ElementType key_t;
    ElementType value_t;
} hash_table_t;

typedef hash_table_t* Map;

/* Built-in Functions */
Map map_create(ElementType key_t, ElementType value_t, u_int8_t capacity);
bool map_insert(Map M, Pointer key, Pointer value);
Pointer map_get(Map M, Pointer key);
bool map_update(Map M, Pointer key, Pointer value); 
bool map_delete(Map M, Pointer key); 
void map_print(Map M);
void map_destroy(Map M);


#endif