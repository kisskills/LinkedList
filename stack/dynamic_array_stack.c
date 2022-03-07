#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define INIT_SIZE 10

struct dynamic_array_stack {
    int64_t* data;
    size_t size;
    size_t top;
};

struct dynamic_array_stack* create_dynamic_array_stack() {
    struct dynamic_array_stack* head = NULL;
    head = malloc(sizeof(struct dynamic_array_stack));
    head->size = INIT_SIZE;
    head->data = malloc(INIT_SIZE * sizeof(int64_t));
    head->top = 0;
    return head;
}

void delete_dynamic_array_stack(struct dynamic_array_stack** stack) {
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

void resize_dynamic_array_stack(struct dynamic_array_stack* stack) {
    stack->size *= 2;
    stack->data = realloc(stack->data, stack->size * sizeof(int64_t));
}

void push_dynamic_array_stack(struct dynamic_array_stack* stack, int64_t data) {
    if (stack->top == stack->size) resize_dynamic_array_stack(stack);
    stack->data[stack->top] = data;
    stack->top++;
}

int64_t pop_dynamic_array_stack(struct dynamic_array_stack* stack) {
    if (stack->top <= 0) exit(1);
    stack->top--;
    return stack->data[stack->top];
}

int64_t peek_dynamic_array_stack(struct dynamic_array_stack* stack) {
    if (stack->top <= 0) exit(1);
    return stack->data[stack->top];
}

void implode_dynamic_array_stack(struct dynamic_array_stack* stack) {
    stack->size = stack->top;
    stack->data = realloc(stack->data, stack->top * sizeof(int64_t));
}

void print_dynamic_array_stack(struct dynamic_array_stack* stack) {
    for (size_t i = 0; i < stack->top; i++)
        printf("%"PRId64" ", stack->data[i]);
    printf("\n");
}

int main() {
    struct dynamic_array_stack* stack = NULL;
    stack = create_dynamic_array_stack();
    printf("size = %zu\n", stack->size);
    for (size_t i = 0; i < 11; i++)
        push_dynamic_array_stack(stack, i + 1);
    print_dynamic_array_stack(stack);
    printf("size = %zu\n", stack->size);

    for (size_t i = 0; i < 10; i++)
        pop_dynamic_array_stack(stack);
    print_dynamic_array_stack(stack);
    implode_dynamic_array_stack(stack);
    printf("size = %zu\n", stack->size);

    delete_dynamic_array_stack(&stack);
    return 0;
}