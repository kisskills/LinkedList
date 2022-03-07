#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

// узел списка
struct double_linkedlist_node {
    int64_t data;
    struct double_linkedlist_node* prev;
    struct double_linkedlist_node* next;
};
// сам список, хранит размер и указатели на первый и последний узлы
struct double_linkedlist {
    size_t size;
    struct double_linkedlist_node* head;
    struct double_linkedlist_node* tail;
};

struct double_linkedlist* create_double_linkedlist() {
    struct double_linkedlist* ptr = NULL;
    ptr = malloc(sizeof(struct double_linkedlist));
    ptr->size = 0;
    ptr->head = ptr->tail = NULL;
    return ptr;
}

void delete_double_linkedlist(struct double_linkedlist** list) {
    struct double_linkedlist_node* ptr = (*list)->head;
    struct double_linkedlist_node* next = NULL;
    while (ptr) {
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
    free(*list);
    *list = NULL;
}

void pushfront_double_linkedlist(struct double_linkedlist* list, int64_t data) {
    struct double_linkedlist_node* ptr = malloc(sizeof(struct double_linkedlist_node));
    ptr->data = data;
    ptr->prev = NULL;
    ptr->next = list->head;
    // если в списке уже был узел, то его указатель на предыдущий меняем на вновь созданный
    if (list->head)
        list->head->prev = ptr;
    // если хвост списка указывал на NULL то переставляем его на созданный узел
    if (!list->tail)
        list->tail = ptr;

    list->head = ptr;
    list->size++;
}

int64_t popfront_double_linkedlist(struct double_linkedlist* list) {
    struct double_linkedlist_node* ptr = list->head;
    int64_t data;
    if (!ptr) exit(1);
    list->head = list->head->next;
    if (list->head)
        list->head->prev = NULL;
    // если в списке был всего один узел, то указатель на хвост тоже надо изменить
    if (list->tail == ptr)
        list->tail = NULL;

    data = ptr->data;
    free(ptr);

    list->size--;
    return data;
}