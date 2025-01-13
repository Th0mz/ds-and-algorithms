#include "array.h"

/* Built-in Functions */
Array arr_create (ElementType elem_t, u_int64_t size) {
    Array array = malloc(sizeof(array_t));
    assert(array != NULL);

    array->fst = malloc(size * elem_t.size);
    assert(array->fst != NULL);

    array->size = size;
    array->elem_t = elem_t;

    return array;
}

Pointer arr_access (Array A, u_int64_t index) {
    assert(A != NULL);
    ElementType T = A->elem_t;

    if (index >= A->size) {
        return NULL;
    }

    return ((char*) A->fst) + (index * T.size);
} 

bool arr_update (Array A, Pointer value, u_int64_t index) {
    assert(A != NULL);
    ElementType T = A->elem_t;

    if (index >= A->size) {
        return false;
    }

    Pointer to_update = ((char*)A->fst) + (index * T.size);
    memcpy(to_update, value, T.size);

    return true;
}

int arr_search (Array A, Pointer value) {
    assert(A != NULL);
    ElementType T = A->elem_t;

    for (int i = 0; i < A->size; i++) {
        Pointer cur = arr_access(A, i);
        if (T.compare(cur, value) == 0) {
            return i;
        }
    }

    return -1;
}

bool arr_insert (Array A, Pointer value, u_int64_t index) {
    assert(A != NULL);
    ElementType T = A->elem_t;
    
    if (index >= A->size) {
        return false;
    }
    
    // move elements 
    u_int64_t move_size = (A->size - index - 1) *  T.size;
    Pointer to_move = malloc(move_size);
    assert(to_move != NULL);
    
    memcpy(to_move, ((char*)A->fst) + (index * T.size), move_size);
    memcpy(((char*)A->fst) + ((index + 1) * T.size), to_move, move_size);

    // insert new element in the created space
    arr_update(A, value, index);
    free(to_move);

    return true;
}

bool arr_delete (Array A, u_int64_t index) {
    assert(A != NULL);
    ElementType T = A->elem_t;

    if (index >= A->size) {
        return false;
    }

    // move elements
    u_int64_t move_size = (A->size - index - 1) *  T.size;
    Pointer to_move = malloc(move_size);
    assert(to_move != NULL);

    memcpy(to_move, ((char*)A->fst) + ((index + 1) * T.size), move_size);
    memcpy((char*)A->fst + (index * T.size), to_move, move_size);

    // remove the last element (it was pushed one index bellow)
    Pointer to_remove = ((char*)A->fst) + ((A->size - 1) * T.size);
    memset(to_remove, 0, T.size);
    
    free(to_move);
    return true;
}

void arr_print(Array A) {
    assert(A != NULL);
    ElementType T = A->elem_t;

    printf("[");
    for (int i = 0; i < A->size; i++) {
        Pointer elem = arr_access(A, i);
        T.print(elem);
        if (i != A->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void arr_destroy (Array A) {
    assert(A != NULL);
    free(A->fst);
    free(A);
}

#ifdef TEST_ARRAY

int main() {
    printf("----- CHARACTER -----\n");
    Array array = arr_create(char_t, 5);
    char tomas[5] = {'t', 'o', 'm', 'a', 's'};

    for (int i = 0; i < 5; i++) {
        arr_update(array, tomas+i, i);
    }

    printf("character 'a' is on index : %d\n", arr_search(array, tomas+3));
    printf("character 'z' is on index : %d\n", arr_search(array, &(char){'z'}));

    arr_insert(array, &(char){'z'}, 2);
    arr_delete(array, 1);

    arr_print(array);
    arr_destroy(array);

    printf("----- STRINGS -----\n");
    array = arr_create(str_t, 5);
    char strings[5][3] = {"ya", "ye", "yi", "yo", "yu" };

    for (int i = 0; i < 5; i++) {
        arr_update(array, strings+i, i);
    }

    printf("string \"ye\" is on index : %d\n", arr_search(array, "ye"));
    printf("string \"joao\" is on index : %d\n", arr_search(array, "joao"));

    arr_insert(array, "joao", 2);
    arr_delete(array, 1);

    arr_print(array);
    arr_destroy(array);
    return 0;
}

#endif