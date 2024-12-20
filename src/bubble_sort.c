#include "../utils/utils.h"

// O(n^2)
void bubble_sort(int *arr, int len) {
    int tmp;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1 - i; j++) {

            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];

                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(void) {

    int arr[] = {0, 4, 5, 2, 1, 9, 3, 6, 7, 8};
    int len = *(&arr + 1) - arr;

    print_num_array(arr, len);

    bubble_sort(arr, len);
    print_num_array(arr, len);

    return 0;
}
