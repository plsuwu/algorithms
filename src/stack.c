/**
 * stack is essentially a LIFO queue - instead of tracking the head and tail, we
 * have a head node containing a pointer to the previously-inserted item
 *
 * [ 0 , 1 ] <-- [ 2 ] (push)
 *   ^   ^
 *   |   head
 *   head.prev
 *
 *   head -->
 * [ 0, 1, 2 ]
 *      ^  ^
 *      |  head
 *      head.prev
 *
 * [ 0 , 1 ] --> [ 2 ] (pop)
 *   ^   ^
 *   |   head
 *   head.prev
 */

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"

typedef struct Node {
    int value;
    struct Node *prev;
} node_t;

typedef struct Stack {
    int length;
    node_t *head;
} stack_t;

void push(stack_t *stack, int item) {
    // also note that in C we dont need to cast this malloc as a node_t pointer
    // (the same goes for the queue implementation)
    //
    // node_t *node = (node_t *)malloc(sizeof(node_t));
    node_t *node = malloc(sizeof(node_t));
    stack->length += 1;

    node->value = item;
    node->prev = NULL;

    // if the stack is empty, we can create the head reference and return
    if (stack->length == 1) {
        stack->head = node;
        return;
    }

    node->prev = stack->head;
    stack->head = node;
}

int pop(stack_t *stack) {
    // only decrement if the stack has items in it
    if (stack->length > 0) {
        stack->length -= 1;
    }

    int popped = stack->head->value;
    node_t *prev_head = stack->head;

    if (stack->length == 0) {
        stack->head = NULL;
    } else {
        stack->head = stack->head->prev;
    }

    free(prev_head);
    return popped;
}

void stack_from_array(int *arr, int arr_len, stack_t *out) {
    for (int i = 0; i < arr_len; i++) {
        push(out, arr[i]);
    }
}

void pop_to_array(stack_t *stack, int stack_len, int *out) {
    for (int i = 0; i < stack_len; i++) {
        out[i] = pop(stack);
    }
}

int main(void) {
    int arr[] = {0, 4, 5, 2, 1, 9, 3, 6, 7, 8};
    int len = *(&arr + 1) - arr;

    printf("starting ");
    print_num_array(arr, len);

    stack_t stack = {0};
    stack_from_array(arr, len, &stack);

    node_t *p = stack.head;
    int iter = 0;

    printf("stack contents: ");
    while (p != NULL) {
        printf("%d", p->value);
        if (iter < stack.length - 1) {
            printf(", ");
        }
        p = p->prev;
        iter += 1;
    }
    printf("\n");

    int *new_arr = malloc(stack.length * sizeof(int));
    pop_to_array(&stack, stack.length, new_arr);

    printf("popped ");
    print_num_array(new_arr, len);

    return 0;
}
