#include <stdio.h>

#include "../utils/utils.h"

int partition(int *arr, int low_index, int high_index) {

    int pivot = arr[high_index];
    int index = low_index - 1;

    for (int i = low_index; i < high_index; i++) {
        if (arr[i] <= pivot) {
            index += 1;

            int tmp = arr[i];
            arr[i] = arr[index];
            arr[index] = tmp;
        }
    }

    index += 1;

    arr[high_index] = arr[index];
    arr[index] = pivot;

    return index;
}

void quicksort(int *arr, int len, int low_index, int high_index) {
    if (low_index >= high_index) {
        return;
    }

    int pivot_index = partition(arr, low_index, high_index);
    quicksort(arr, len, low_index, pivot_index - 1);
    quicksort(arr, len, pivot_index + 1, high_index);
}

int main(void) {
    int arr[] = {0, 4, 5, 2, 1, 9, 3, 6, 7, 8};
    int len = *(&arr + 1) - arr;

    printf("initial ");
    print_num_array(arr, len);

    quicksort(arr, len, 0, len - 1);

    printf("sorted ");
    print_num_array(arr, len);

    return 0;
}
