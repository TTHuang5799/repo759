#include <omp.h>
#include "msort.h"

// Merge function to merge two sorted halves
void merge(int* arr, int* temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

// Recursive parallel merge sort
void parallel_merge_sort(int* arr, int* temp, int left, int right, int ts) {
    if (right - left <= ts) {
        // Base case: small enough array, use serial sort
        std::sort(arr + left, arr + right + 1);
        return;
    }

    int mid = left + (right - left) / 2;

    // Parallelize the recursive calls with tasks
    #pragma omp task shared(arr, temp)
    parallel_merge_sort(arr, temp, left, mid, ts);

    #pragma omp task shared(arr, temp)
    parallel_merge_sort(arr, temp, mid + 1, right, ts);

    #pragma omp taskwait
    merge(arr, temp, left, mid, right);
}

// Interface function called by task3.cpp
void msort(int* arr, int n, int ts) {
    int* temp = new int[n];
    #pragma omp parallel
    {
        #pragma omp single
        parallel_merge_sort(arr, temp, 0, n - 1, ts);
    }
    delete[] temp;
}
