#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} node_t;

typedef struct Queue {
    int length;
    node_t *head;
    node_t *tail;
} queue_t;

void enqueue(queue_t *queue, int item) {
    // alloc new memory for the node - note that we don't have to typecast the
    // malloc like this in C
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL) {
        return; // allocation failure
    }

    node->value = item;
    node->next = NULL;
    queue->length += 1;

    // we have an empty queue, so we want to create a single-node queue
    if (queue->length == 1) {
        // one value (0 links), so we set the head to point at the current node
        // and the tail to point to the head; there is no next item to point to
        // so head.next & tail.next will be NULL
        queue->head = node;
        queue->tail = queue->head;

        return;
    }

    // adjust the tail's next pointer before updating the tail pointer to retain
    // list integrity:
    /**
     ----------------------------------
     ```
      queue->tail = node;
     ```

     breaks our list link:

     [A] -> [B] -> [C] -> NULL   [D]
                                 ^
                                 tail
     ----------------------------------
     ----------------------------------
     ```
      queue->tail = node;
      queue->tail->next = node;
     ```
     creates a node cycle:
     [A] -> [B] -> [C] -> [D] ─┐
                          ^    |
                          tail └──┘
     ----------------------------------

    */

    queue->tail->next = node;
    queue->tail = node;
}

int dequeue(queue_t *queue) {
    // if there is nothing to dequeue (i.e, if the queue is empty), return -1 to
    // indicate an error
    // (this might be something like `undefined` or a `Result<Error>` type
    // depending on the type system)
    if (queue->length == 0) {
        return -1;
    }

    // create a copy of the current head value to return, and a pointer to the
    // previous head to free its memory after updating the head pointer
    int curr = queue->head->value;
    node_t *prev_head = queue->head;

    // update the queue length and head pointer
    queue->head = queue->head->next;
    queue->length -= 1;

    // if we just removed the last element from the queue, set head/tail
    // pointers to NULL
    if (queue->length == 0) {
        queue->head = NULL;
        queue->tail = NULL;
    }

    free(prev_head); // free the dequeued node's memory
    return curr;
}

void queue_from_array(int *arr, int arr_len, queue_t *out) {
    for (int i = 0; i < arr_len; i++) {
        enqueue(out, arr[i]);
    }
}

void dequeue_to_array(queue_t *queue, int queue_len, int *out, int out_len) {
    if (out_len != queue_len) {
        return;
    }

    for (int i = 0; i < queue_len; i++) {
        out[i] = dequeue(queue);
    }
}

int main(void) {
    int arr[] = {0, 4, 5, 2, 1, 9, 3, 6, 7, 8};
    int len = *(&arr + 1) - arr;

    queue_t queue = {0};
    queue_from_array(arr, len, &queue);

    printf("queue contents: ");
    node_t *p = queue.head;
    int iters = 0;
    while (p != NULL) {
        printf("%d", p->value);
        p = p->next;
        if (iters != queue.length - 1) {
            printf(", ");
        }
        iters += 1;
    }
    printf("\n");

    int *arr_from_queue = malloc(queue.length * sizeof(int));
    int new_len = queue.length;

    dequeue_to_array(&queue, queue.length, arr_from_queue, new_len);
    printf("dequeue into array result: [");
    for (int i = 0; i < new_len; i++) {
        printf("%d", arr_from_queue[i]);
        if (i < new_len - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}

/*void peek(queue_t *queue) {}*/
