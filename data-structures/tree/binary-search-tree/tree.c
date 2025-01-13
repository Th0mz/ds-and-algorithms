#include "tree.h"

/* Built-in Functions */
Tree bst_create (ElementType T) {
    Tree tree = malloc(sizeof(struct tree_t));
    assert(tree != NULL);

    tree->root = NULL;
    tree->size = 0;
    tree->elem_t = T;

    return tree;
}

void bst_insert (Tree T, Pointer value) {
    assert(T != NULL);
    ElementType E = T->elem_t;

    // setup new node information 
    Node new_node = malloc(sizeof(struct node_t));
    assert(new_node != NULL);
    new_node->value = E.create(value);
    new_node->left = NULL; new_node->right = NULL;

    // find a empty leaf place that adheres to the bst restriction
    Node* cur_node = &T->root;
    while (*cur_node != NULL) {
        Pointer cur_value = (*cur_node)->value;
        /* check which brach should take the new value to 
           maintain the bst property */
        if (E.compare(cur_value, value) > 0) {
            cur_node = &(*cur_node)->left;
        } else {
            cur_node = &(*cur_node)->right;
        }
    }

    *cur_node = new_node;
}

bool bst_search (Tree T, Pointer value) {
    assert(T != NULL);
    ElementType E = T->elem_t;

    Node cur_node = T->root;
    while (cur_node != NULL) {
        int value_cmp = E.compare(cur_node->value, value);

        // check if the current node value is the same as the 
        // value we are looking for
        if (value_cmp == 0) {
            return true;
        // if it isn't the same we should choose the branch 
        // to explore based on the bst properties
        } else if (value_cmp > 0) {
            cur_node = cur_node->left;
        } else {
            cur_node = cur_node->right;
        }
    }

    return false;
}

Pointer find_max(Node node) {
    // the minimum value of the bst with node as root is the left most leaf
    if (node == NULL) {
        return NULL;
    } else if (node->right == NULL) {
        return node->value;
    } else {
        return find_max(node->right);
    }
}

Pointer find_min(Node node) {
    // the minimum value of the bst with node as root is the left most leaf
    if (node == NULL) {
        return NULL;
    } else if (node->left == NULL) {
        return node->value;
    } else {
        return find_min(node->left);
    }
}

bool delete_node (Node* pointer, Pointer value, ElementType E) {
    Node cur = *pointer;
    if (cur == NULL) {
        return false;
    }

    int cmp = E.compare(cur->value, value);
    // element to remove found
    if (cmp == 0) {
            // case 1: deleting a leaf node 
            //    - just remove it
            if (cur->left == NULL && cur->right == NULL) {
                E.destroy(cur->value);
                free(cur);

                *pointer = NULL;
                return true;
            }
            // case 2: deleting a node with 1 child 
            //   - remove it and make its child take his place
            else if (cur->left == NULL || cur->right == NULL) {
                Node child = cur->left != NULL ? cur->left : cur->right;
                E.destroy(cur->value);
                free(cur);

                *pointer = child;
                return true;
            }

            // case 3: deleting a node with 2 children
            //   - find a leaf node that can replace the value that is being deleted without 
            //     breaking the bst property, this node is either the largest element of the left side
            //     (which is bigger than all left side element and smaller than all right 
            //     side ones maintaining then the bst property) or the lowest right side element (for the same reason)
            //   - also if the value is the lowest of the right subtree it means that by definition it can only be a leaf node
            //     or a element with a right branch, since if it had a left node it would be the smallest but the one on the 
            //     left of it, so removing the lowest element is easy is can be boiled down to either case 1 or 2
            else {
                // swap current value with the minium value
                Pointer min_value = find_min(cur->right);
                E.destroy(cur->value);
                cur->value = E.create(min_value);

                // delete duplicate value
                return delete_node(&cur->right, min_value, E);
            }

    // keep traversing the tree in search for the element to remove
    } else if (cmp > 0) {
        return delete_node(&cur->left, value, E);
    } else {
        return delete_node(&cur->right, value, E);
    }
}

bool bst_delete (Tree T, Pointer value) {
    assert(T != NULL);
    return delete_node(&T->root, value, T->elem_t);
}

int get_depth(Node node) {
    if (node == NULL) {
        return 0;
    } else {
        return 1 + max(get_depth(node->left), get_depth(node->right));
    }
}

int bst_get_depth(Tree T) {
    return get_depth(T->root);
}

char* generate_spaces(int n) {
    char* spaces = calloc(n + 1, sizeof(char));
    assert(spaces != NULL);
    memset(spaces, ' ', n);

    return spaces; 
}

void bst_print (Tree T) {
    assert(T != NULL);
    ElementType E = T->elem_t;

    Queue q = q_create(ptr_t);
    int i = 0, h = 0, depth = bst_get_depth(T);
    q_enqueue(q, T->root);

    while (h < depth) {
        char* indentation = generate_spaces(pow(2, depth - h - 1) - 1);
        char* separator = generate_spaces(pow(2, depth - h) - 1);

        printf("%s", indentation);

        int num_elems = pow(2, h);
        for (int i = 0; i < num_elems; i ++) {
            Node node = (Node) q_dequeue(q);

            if (node == NULL) {
                printf(".");
                q_enqueue(q, NULL); q_enqueue(q, NULL);
            } else {
                E.print(node->value);
                q_enqueue(q, node->left);
                q_enqueue(q, node->right);
            }

            printf("%s", separator);
        }

        printf("\n");
        h++;
    }

    q_destroy(q);
}

void destroy_node(Node node, ElementType E) {
    if (node == NULL) {
        return;
    }

    destroy_node(node->left, E);
    destroy_node(node->right, E);
    E.destroy(node->value);
    free(node);
    
}

void bst_destroy (Tree T) {
    assert(T != NULL);
    destroy_node(T->root, T->elem_t);
    free(T);
}

#ifdef TEST_TREE

int main () {
    Tree tree = bst_create(int_t);
    bst_print(tree);

    bst_insert(tree, &(int){5});
    bst_insert(tree, &(int){3});
    bst_insert(tree, &(int){1});
    bst_insert(tree, &(int){7});
    bst_insert(tree, &(int){4});
    bst_insert(tree, &(int){8});
    bst_insert(tree, &(int){9});
    bst_insert(tree, &(int){6});


    printf("case 1 - 1 was%sdeleted\n", bst_delete(tree, &(int){1}) == true ? " " : " not ");
    printf("case 2 - 8 was%sdeleted\n", bst_delete(tree, &(int){8}) == true ? " " : " not ");
    printf("case 3 - 5 was%sdeleted\n", bst_delete(tree, &(int){5}) == true ? " " : " not ");

    bst_print(tree);
    bst_destroy(tree);
    return 0;
}

#endif