#include "utils.h"

void print_num_array(int *arr, int len) {
    printf("Array items: [");
    for (int i = 0; i < len; i++) {
        printf("%d", arr[i]);

        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
