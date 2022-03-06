#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct linked_list {
    int64_t data;
    struct linked_list* next;
};

void push(struct linked_list** root, int64_t data) {
    if (!(*root)) {
        *root = malloc(sizeof(struct linked_list));
        (*root)->data = data;
        (*root)->next = NULL;
    } else {
        push(&((*root)->next), data);
    }
}

struct linked_list* find_node(struct linked_list* root, int64_t data) {
    if (root) {
        if (root->data == data)
            return root;
        else
            return find_node(root->next, data);
    }
    return root;
}

void add_node(struct linked_list* elem, int64_t data) {
    if (elem) {
        struct linked_list* new = malloc(sizeof(struct linked_list));
        new->data = data;
        new->next = elem->next;
        elem->next = new;
    }
}

void rm_node(struct linked_list** root, int64_t data) {
    struct linked_list* ptr = find_node(*root, data);
    if (*root && ptr) {
        if (ptr == *root) {
            *root = (*root)->next;
            free(ptr);
        } else {
            struct linked_list* ptr1 = *root;
            while (ptr1->next != ptr) ptr1 = ptr1->next;
            ptr1->next = ptr->next;
            free(ptr);
        }
    }
}

void print_list(struct linked_list* root) {
    if (root) {
        printf("%"PRId64" ", root->data);
        print_list(root->next);
    }
}

void destroy_list(struct linked_list** root) {
    if (*root) {
        struct linked_list* ptr = (*root)->next;
        while (ptr) {
            free(*root);
            *root = ptr;
            ptr = (*root)->next;
        }
        free(*root);
        *root = NULL;
    }
}

int main() {
    struct linked_list* root = NULL;
    push(&root, 1);
    push(&root, 2);
    push(&root, 4);
    print_list(root);
    printf("\n");

    add_node(find_node(root, 2), 3);
    print_list(root);
    printf("\n");   

    rm_node(&root, 4);
    rm_node(&root, 3);
    rm_node(&root, 1);
    print_list(root);
    printf("\n");

    destroy_list(&root);
    return 0;
}