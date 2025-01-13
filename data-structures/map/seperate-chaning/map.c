#include "map.h"

/* Built-in Functions */
Map map_create(ElementType key_t, ElementType value_t, u_int8_t capacity) {
    Map map = malloc(sizeof(hash_table_t));
    assert(map != NULL);

    map->buckets = calloc(sizeof(bucket_t), get_size(capacity));
    assert(map->buckets != NULL);
    map->capacity = capacity;
    map->elements = 0;
    map->key_t = key_t;
    map->value_t = value_t;

    return map;
}

bool map_insert(Map M, Pointer key, Pointer value) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;

    u_int64_t index = K.hash(key) % get_size(M->capacity);
    /* check if key was already inserted */
    bool added = map_update(M, key, value);
    if (!added) {
        Bucket bucket = malloc(sizeof(bucket_t));
        assert(bucket != NULL);

        bucket->key = K.create(key);
        bucket->value = K.create(value);
        bucket->next = M->buckets[index];

        M->buckets[index] = bucket;
        M->elements++;
    }

    return true;
}

Pointer map_get(Map M, Pointer key) {
    assert(M != NULL);
    ElementType K = M->key_t;

    u_int64_t index = K.hash(key) % get_size(M->capacity);
    for (Bucket bucket = M->buckets[index]; bucket != NULL; bucket = bucket->next) {
        if (K.compare(key, bucket->key) == 0) {
            return bucket->value;
        }
    }

    return NULL;
}

bool map_update(Map M, Pointer key, Pointer value) {
    assert(M != NULL);

    ElementType K = M->key_t;
    ElementType V = M->value_t;
    u_int64_t index = K.hash(key) % get_size(M->capacity);

    for (Bucket bucket = M->buckets[index]; bucket != NULL; bucket = bucket->next) {
        if (K.compare(key, bucket->key) == 0) {
            V.destroy(bucket->value);
            bucket->value = V.create(value);
            return true;
        }
    }

    return false;
}

bool map_delete(Map M, Pointer key) {
    assert(M != NULL);

    ElementType V = M->value_t;
    ElementType K = M->key_t;
    u_int64_t index = K.hash(key) % get_size(M->capacity);

    Bucket prev = NULL;
    for (Bucket bucket = M->buckets[index]; bucket != NULL; prev = bucket, bucket = bucket->next) {
        if (K.compare(key, bucket->key) == 0) {
            /* check if it is a deletion from the begging of the bucket */
            if (prev == NULL) {
                M->buckets[index] = bucket->next;
            } else {
                prev->next = bucket->next;
            }

            /* destroy element */
            K.destroy(bucket->key);
            V.destroy(bucket->value);
            free(bucket);
            
            return true;
        }
    }

    return false;
}

bool map_search(Map M, Pointer key) {
    assert(M != NULL);
    ElementType K = M->key_t;
    u_int64_t index = K.hash(key) % get_size(M->capacity);

    for (Bucket bucket = M->buckets[index]; bucket != NULL; bucket = bucket->next) {
        if (K.compare(key, bucket->key) == 0) {
            return true;
        }
    }

    return false;
}


void map_print(Map M) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;

    printf("{\n");
    for (int i = 0; i < get_size(M->capacity); i++) {
        printf("  ");
        for (Bucket bucket = M->buckets[i]; bucket != NULL; bucket = bucket->next) {
            printf("(");
            K.print(bucket->key);
            printf(", ");
            V.print(bucket->value);
            printf(") -> ");
        }

        printf("NULL\n");
    }

    printf("}\n");

}

void map_destroy(Map M) {
    assert(M != NULL);
    ElementType K = M->key_t;
    ElementType V = M->value_t;

    for (int i = 0; i < get_size(M->capacity); i++) {
        Bucket bucket = M->buckets[i];
        while (bucket != NULL) {
            Bucket tmp = bucket;
            bucket = bucket->next;

            /* delete node */
            K.destroy(tmp->key);
            V.destroy(tmp->value);
            free(tmp);
        }
    }

    free(M->buckets);
    free(M);
}

#ifdef TEST_MAP

int main() {
    Map map = map_create(str_t, str_t, 2);

    map_insert(map, "key", "value");
    map_insert(map, "key0", "value");
    map_insert(map, "key1", "value");
    map_insert(map, "key2", "value");
    map_insert(map, "key2", "value1");
    map_insert(map, "kdy3", "kdy3-value");

    map_delete(map, "key2");
    map_delete(map, "key0");

    printf("o valor associado à key 'key2' é ");
    str_t.print(map_get(map, "key2"));
    printf("\n");
    printf("o valor associado à key 'kdy3' é ");
    str_t.print(map_get(map, "kdy3"));
    printf("\n");

    map_print(map);
    map_destroy(map);
    return 0;
}

#endif