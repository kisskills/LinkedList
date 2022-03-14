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

void pushback_double_linkedlist(struct double_linkedlist* list, int64_t data) {
    struct double_linkedlist_node* ptr = malloc(sizeof *ptr);
    ptr->data = data;
    ptr->prev = list->tail;
    ptr->next = NULL;

    if (list->tail)
        list->tail->next = ptr;
    if (!list->head)
        list->head = ptr;

    list->tail = ptr;
    list->size++;
}

int64_t popback_double_linkedlist(struct double_linkedlist* list) {
    struct double_linkedlist_node* ptr = list->tail;
    int64_t data;
    if (!ptr) exit(2);
    list->tail = list->tail->prev;
    if (list->tail)
        list->tail->next = NULL;
    if (list->head == ptr)
        list->head = NULL;

    data = ptr->data;
    free(ptr);

    list->size--;
    return data;
}

struct double_linkedlist_node* find_node_double_linkedlist(struct double_linkedlist* list, int64_t data) {
    struct double_linkedlist_node* ptr = list->head;
    char flag = 0;
    
    while (ptr) {
        if (ptr->data == data) {
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (flag == 1)
        return ptr;
    else
        return NULL;
}

struct double_linkedlist_node* find_nth_double_linkedlist(struct double_linkedlist* list, size_t index) {
    struct double_linkedlist_node* ptr = NULL;
    size_t i;

    if (index < list->size / 2) {
        ptr = list->head;
        i = 0;
        while (ptr && i < index) {
            ptr = ptr->next;
            i++;
        }
    } else {
        ptr = list->tail;
        i = list->size - 1;
        while (ptr && i > index) {
            ptr = ptr->prev;
            i--;
        }
    }
    return ptr;
}

void insert_double_linkedlist(struct double_linkedlist* list, size_t index, int64_t data) {
    struct double_linkedlist_node* new = NULL;
    struct double_linkedlist_node* elem = NULL;
    elem = find_nth_double_linkedlist(list, index);
    if (!elem) exit(3);
    new = malloc(sizeof *new);

    new->data = data;
    new->next = elem->next;
    new->prev = elem;
    // если вставляем в середину, надо изменить указатель prev следующего э-та в исходном списке
    if (elem->next)
        elem->next->prev = new;
    elem->next = new;
    // если вставляем в конец списка, надо изменить tail
    if (!new->next) {
        list->tail = new;
    }
    list->size++;
}

// void rm_double_linkedlist(struct double_linkedlist* list, size_t index) {

// }

void print_double_linkedlist(struct double_linkedlist* list, void (*fun)(void*)) {
    struct double_linkedlist_node* ptr = list->head;
    while (ptr) {
        fun(ptr);
        ptr = ptr->next;
    }
    printf("\n");
}

void print_double_linkedlist_node(void* node) {
    printf("%"PRId64" ",((struct double_linkedlist_node*) node)->data);
}

int main() {
    struct double_linkedlist* list = create_double_linkedlist();

    for(size_t i = 6; i < 11; i++)
        pushback_double_linkedlist(list, i + 1);
    print_double_linkedlist(list, print_double_linkedlist_node);
    for(size_t i = 0; i < 5; i++)
        popback_double_linkedlist(list);
    
    for(size_t i = 0; i < 5; i++)
        pushfront_double_linkedlist(list, i + 1);
    print_double_linkedlist(list, print_double_linkedlist_node);
    for(size_t i = 0; i < 4; i++)
        popfront_double_linkedlist(list);
    print_double_linkedlist(list, print_double_linkedlist_node);

    printf("Node with data '1' adress = %p\n", find_node_double_linkedlist(list, 1));
    printf("Node with data '100' adress = %p\n", find_node_double_linkedlist(list, 100));

    // insert_double_linkedlist(list, 0, 2);
    // insert_double_linkedlist(list, 0, 11);
    // insert_double_linkedlist(list, 2, 3);
    // insert_double_linkedlist(list, 2, 22);
    print_double_linkedlist(list, print_double_linkedlist_node);

    delete_double_linkedlist(&list);
    return 0;
}