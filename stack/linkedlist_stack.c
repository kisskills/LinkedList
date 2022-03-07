#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct linkedlist_stack {
    int64_t data;
    struct linkedlist_stack* next;
};

void push_linkedlist_stack(struct linkedlist_stack** head, int64_t data) {
    struct linkedlist_stack* ptr = malloc(sizeof(struct linkedlist_stack));
    ptr->data = data;
    ptr->next = *head;
    *head = ptr;
}

int64_t pop_linkedlist_stack(struct linkedlist_stack** head) {
    if (!head) exit(1);
    struct linkedlist_stack* ptr = *head;
    int64_t data = ptr->data;
    *head = (*head)->next;
    free(ptr);
    return data;
}

int64_t peek_linkedlist_stack(struct linkedlist_stack* head) {
    if (!head) exit(1);
    return head->data;
}

void print_linkedlist_stack(struct linkedlist_stack* head) {
    while (head) {
        printf("%"PRId64" ", head->data);
        head = head->next;
    }
    printf("\b\n");
}

size_t size_linkedlist_stack(struct linkedlist_stack* head) {
    size_t size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

void destroy_linkedlist_stack(struct linkedlist_stack** head) {
    struct linkedlist_stack* ptr = NULL;
    while (*head) {
        ptr = *head;
        *head = (*head)->next;
        free(ptr);
    }
}

int main() {
    struct linkedlist_stack* head = NULL;
    for (size_t i = 0; i < 20; i++)
        push_linkedlist_stack(&head, i);
    printf("size = %lu\n", size_linkedlist_stack(head));
    print_linkedlist_stack(head);

    for (size_t i = 0; i < 10; i++)
        pop_linkedlist_stack(&head);
    printf("size = %lu\n", size_linkedlist_stack(head));
    print_linkedlist_stack(head);
   
    destroy_linkedlist_stack(&head);
    return 0;
}
