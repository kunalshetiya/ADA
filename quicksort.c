#include <stdio.h>

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function (pivot = first element)
int partition(int arr[], int start, int end) {
    int pivot = arr[start];
    int count = 0;

    // Count elements <= pivot
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot) {
            count++;
        }
    }

    int pivotIndex = start + count;
    swap(&arr[pivotIndex], &arr[start]);

    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < pivotIndex && j > pivotIndex) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    return pivotIndex;
}

// Quick Sort function
void quicksort(int arr[], int start, int end) {
    if (start >= end)
        return;

    int pivotIndex = partition(arr, start, end);

    quicksort(arr, start, pivotIndex - 1);
    quicksort(arr, pivotIndex + 1, end);
}

// Driver code
int main() {
    int arr[] = {2, 5, 7, 7, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}