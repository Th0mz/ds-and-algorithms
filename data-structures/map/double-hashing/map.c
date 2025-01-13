#include "map.h"

/* Built-in Functions */
Map map_create(ElementType key_t, ElementType value_t, u_int8_t capacity) {
    Map map = malloc(sizeof(hash_table_t));
    assert(map != NULL);

    if (capacity <= 0) {
        return NULL;
    }

    map->buckets = calloc(sizeof(bucket_t), get_size(capacity));
    assert(map->buckets != NULL);
    
    map->capacity = capacity;
    map->hash_prime = capacity - 1;
    map->elements = 0;
    map->key_t = key_t;
    map->value_t = value_t;
    return map;
}

bool map_insert(Map M, Pointer key, Pointer value) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;
    u_int64_t capacity = get_size(M->capacity);

    u_int64_t hash_value = K.hash(key);
    u_int64_t index = hash_value % capacity;
    u_int64_t step = hash_func2(get_size(M->hash_prime), hash_value);
    u_int64_t deleted_index = -1;

    /* find bucket position */
    Bucket bucket = &M->buckets[index];
    u_int64_t buckets_checked = 0;
    while (buckets_checked < capacity) {

        // empty spot found just add it 
        if (bucket->state == EMPTY) {
            break;

        // deleted spot found we store it and keep searching to make sure that 
        // the key doesnt exist in next occurrences 
        } else if (bucket->state == DELETED) {

            /* only update the first time around */
            deleted_index = (deleted_index == -1) ? index : deleted_index;
        
        // found the old version of the element we are adding
        } else if (bucket->state == OCCUPIED && K.compare(key, bucket->key) == 0) {
            K.destroy(bucket->key);
            V.destroy(bucket->value);
            // REFACTOR : to make the next code work 
            deleted_index = -1;
            M->elements--;
            break;
        }

        /* iteration update */
        index = (index + step) % capacity;
        bucket = &M->buckets[index];
        buckets_checked++;
    }

    /* all buckets checked and there is no space for the element */
    if (deleted_index == -1 && buckets_checked >= capacity) {
        // TODO : implement rehashing
        printf("error : no space in the map\n");
        return false;
    }

    // if a deleted index was found before make sure the bucket 
    // updated is the deleted empty spot 
    index = (deleted_index == -1) ? index : deleted_index;
    bucket = &M->buckets[index];

    bucket->key = K.create(key);
    bucket->value = V.create(value);
    bucket->hash = hash_value;
    bucket->state = OCCUPIED;
    M->elements++;
    
    return true;
}

Pointer map_get(Map M, Pointer key) {
    assert(M != NULL);
    ElementType K = M->key_t;
    u_int64_t capacity = get_size(M->capacity);

    u_int64_t hash_value = K.hash(key);
    u_int64_t index = hash_value % capacity;
    u_int64_t step = hash_func2(get_size(M->hash_prime), hash_value);

    Bucket bucket = &M->buckets[index];
    u_int64_t buckets_checked = 0;
    while (bucket->state != EMPTY && buckets_checked < capacity) {
        
        if (K.compare(key, bucket->key) == 0) {
            return bucket->value;
        }

        /* iteration update */
        index = (index + step) % capacity;
        bucket = &M->buckets[index];
        buckets_checked++;
    }

    return NULL;
}


bool map_update(Map M, Pointer key, Pointer value) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;
    u_int64_t capacity = get_size(M->capacity);

    u_int64_t hash_value = K.hash(key);
    u_int64_t index = hash_value % capacity;
    u_int64_t step = hash_func2(get_size(M->hash_prime), hash_value);

    Bucket bucket = &M->buckets[index];
    u_int64_t buckets_checked = 0;
    while (bucket->state != EMPTY && buckets_checked < capacity) {
        
        if (K.compare(key, bucket->key) == 0) {
            V.destroy(bucket->value);
            bucket->value = V.create(value);
            return true;
        }

        /* iteration update */
        index = (index + step) % capacity;
        bucket = &M->buckets[index];
        buckets_checked++;
    }

    return false;
}


bool map_delete(Map M, Pointer key) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;
    u_int64_t capacity = get_size(M->capacity);

    u_int64_t hash_value = K.hash(key);
    u_int64_t index = hash_value % capacity;
    u_int64_t step = hash_func2(get_size(M->hash_prime), hash_value);

    Bucket bucket = &M->buckets[index];
    u_int64_t buckets_checked = 0;
    while (bucket->state != EMPTY && buckets_checked < capacity) {
        
        if (K.compare(key, bucket->key) == 0) {
            K.destroy(bucket->key);
            V.destroy(bucket->value);
            bucket->state = DELETED;
            M->elements--;
            return true;
        }

        /* iteration update */
        index = (index + step) % capacity;
        bucket = &M->buckets[index];
        buckets_checked++;
    }

    return false;
}


void map_print(Map M) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;

    printf("{ ");
    for (int i = 0; i < get_size(M->capacity); i++) {
        Bucket bucket = &M->buckets[i];
        if (bucket->state == EMPTY || bucket->state == DELETED) {
            continue;
        }

        printf("(");
        K.print(bucket->key);
        printf(", ");
        V.print(bucket->value);
        printf("), ");
    }
    printf(" }\n");
}

void map_destroy(Map M) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;

    for (int i = 0; i < get_size(M->capacity); i++) {
        Bucket bucket = &M->buckets[i];
        if (M->buckets[i].state == OCCUPIED) {
            K.destroy(bucket->key);
            V.destroy(bucket->value);
        }
    }  

    free(M->buckets);
    free(M);
}

#ifdef TEST_MAP

int main() {
    Map map = map_create(str_t, str_t, 2);

    map_insert(map, "key", "value");
    map_insert(map, "key1", "value");
    map_insert(map, "key2", "value");
    map_insert(map, "key3", "value");
    map_insert(map, "key4", "value");
    map_insert(map, "key4", "value4");

    map_insert(map, "key5", "value");
    map_insert(map, "key6", "value");
    
    map_update(map, "key1", "value1");
    map_update(map, "key2", "value2");
    map_update(map, "key6", "value6");

    map_delete(map, "key");
    map_delete(map, "key6");
    map_delete(map, "key4");

    map_print(map);

    map_insert(map, "key5", "value");
    map_print(map);

    map_insert(map, "key6", "value");

    map_print(map);
    map_destroy(map);
    return 0;
}

#endif