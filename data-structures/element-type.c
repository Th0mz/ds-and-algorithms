#include "./element-type.h"

/* concrete integer type */
Pointer create_int (Pointer value) {
    Pointer new_elem = malloc(sizeof(int));
    assert(new_elem != NULL);
    memcpy(new_elem, value, sizeof(int));

    return new_elem;
}

int compare_int (Pointer a, Pointer b) {
    int va = *(int*) a;
    int vb = *(int*) b;

    return (va > vb) - (va < vb);
}

void print_int(Pointer elem) {
    if (elem != NULL) {
        int int_elem = *(int *)elem;
        printf("%d", int_elem);
    } else {
        printf("NULL");
    }
}

void destroy_int(Pointer value) {
    free(value);
}

const ElementType int_t = {
    .size = sizeof(int),
    .create = create_int,
    .compare = compare_int,
    .print = print_int,
    .destroy = destroy_int,
    .hash = NULL
};


/* concrete character type */
Pointer create_char (Pointer value) {
    Pointer new_elem = malloc(sizeof(char));
    assert(new_elem != NULL);
    memcpy(new_elem, value, sizeof(char));

    return new_elem;
}

int compare_char (Pointer a, Pointer b) {
    char va = *(char*) a;
    char vb = *(char*) b;
    
    return (va > vb) - (va < vb);
}

void print_char(Pointer elem) {
    if (elem != NULL) {
        char char_elem = *(char *)elem;
        printf("%c", char_elem);
    } else {
        printf("NULL");
    }
}

void destroy_char(Pointer value) {
    free(value);
}

const ElementType char_t = {
    .size = sizeof(char),
    .create = create_char,
    .compare = compare_char,
    .print = print_char,
    .destroy = destroy_char,
    .hash = NULL
};

/* concrete string type */
Pointer create_str (Pointer value) {
    assert(value != NULL);
    
    Pointer new_elem = strdup(value);
    assert(new_elem != NULL);

    return new_elem;
}

int compare_str (Pointer a, Pointer b) {
    return strcmp(a, b);
}

void print_str(Pointer elem) {
    if (elem != NULL) {
        char* str_elem = (char *)elem;
        printf("\"%s\"", str_elem);
    } else {
        printf("NULL");
    }
}

void destroy_str(Pointer value) {
    if (value != NULL) {
        free(value);
    }
}

// simple hash: sum of all characters
u_int64_t hash_str1(Pointer value) {
    assert(value != NULL);
    const char* str = (const char*) value;

    u_int64_t i, sum = 0;
    for(i = 0; str[i] != '\0'; i++)
        sum += str[i];
    return sum;
}

const ElementType str_t = {
    .size = sizeof(char*),
    .create = create_str,
    .compare = compare_str,
    .print = print_str,
    .destroy = destroy_str,
    .hash = hash_str1
};

/* concrete pointer type */
Pointer create_ptr (Pointer value) {
    return value;
}

int compare_ptr (Pointer a, Pointer b) {
    return (a > b) - (a < b);
}

void print_ptr(Pointer elem) {
    if (elem != NULL) {
        printf("%p", elem);
    } else {
        printf("NULL");
    }
}

void destroy_ptr(Pointer value) {}

const ElementType ptr_t = {
    .size = sizeof(void*),
    .create = create_ptr,
    .compare = compare_ptr,
    .print = print_ptr,
    .destroy = destroy_ptr,
    .hash = NULL
};



