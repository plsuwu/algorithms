// technically this is a doubly linked list

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} node_t;

typedef struct LinkedList {
    int length;
    node_t *head;
    node_t *tail;
} linked_list_t;

node_t *get_at(int index, linked_list_t *list) {
    node_t *curr = list->head;
    int i = 0;

    while (i < index && curr != NULL) {
        curr = curr->next;
        i += 1;
    }

    return curr;
}

node_t *get_eq(int item, linked_list_t *list) {
    node_t *curr = list->head;
    int i = 0;

    while (i < list->length && curr != NULL) {
        if (curr->value == item) {
            break;
        }
        curr = curr->next;
        i += 1;
    }

    return curr;
}

int remove_node(node_t *node, linked_list_t *list) {
    list->length -= 1;
    int val = node->value;

    if (list->length == 0) {
        list->head = NULL;
        list->tail = list->head;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    if (node == list->head) {
        list->head = node->next;
    }

    if (node == list->tail) {
        list->tail = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;

    free(node);
    return val;
}

int remove_at(int index, linked_list_t *list) {
    node_t *node = get_at(index, list);
    if (node == NULL) {
        return -1;
    }

    return remove_node(node, list);
}

int remove_eq(int item, linked_list_t *list) {
    node_t *curr = get_eq(item, list);
    if (curr == NULL) {
        return -1;
    }

    return remove_node(curr, list);
}

void prepend(int item, linked_list_t *list) {
    node_t *node = malloc(sizeof(int));
    node->value = item;

    list->length += 1;
    if (list->length == 1) {
        list->head = node;
        list->tail = list->head;

        return;
    }

    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

void append(int item, linked_list_t *list) {
    node_t *node = malloc(sizeof(int));
    node->value = item;

    list->length += 1;
    if (list->length == 1) {
        list->tail = node;
        list->head = list->tail;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
}

void insert_at(int item, int index, linked_list_t *list) {
    // index outside of bounds
    if (index > list->length || index < 0) {
        return;
    };

    // if we're inserting at an index eq to the current length of our list, we
    // are technically appending to the list, so we can just call that function
    if (index == list->length) {
        append(item, list);
        return;
    }

    // similarly, if the given index is 0, we are prepending to our list, so we
    // can just call that function and return
    if (index == 0) {
        prepend(item, list);
        return;
    }

    node_t *curr = get_at(index, list);

    // create new node and attach at current node index
    node_t *node = malloc(sizeof(int));
    list->length += 1; // increment

    node->next = curr;
    node->prev = curr->prev;

    curr->prev = node;
    if (curr->prev) {
        curr->prev->next = curr;
    }
}

void print_nodes(linked_list_t *list) {
    node_t *p = list->head;
    int i = 0;

    printf("[ ");
    while (p != NULL) {
        printf("%d", p->value);
        if (i < list->length - 1) {
            printf(", ");
        }

        p = p->next;
        i += 1;
    }
    printf(" ]\n");
}

int main(void) {
    linked_list_t list = {0};
    append(1, &list);
    append(2, &list);
    append(3, &list);

    prepend(4, &list);
    prepend(9, &list);
    prepend(4, &list);

    printf("nodes: ");
    print_nodes(&list);

    printf("removing '4': ");
    remove_eq(4, &list);

    print_nodes(&list);
    printf("node @ idx '3' == 2 -> %d\n", get_at(3, &list)->value);

    return 0;
}
