#include "msort.h"
#include <omp.h>

void merge(int* arr, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t n1 = mid - left + 1;
    std::size_t n2 = right - mid;

    // Allocate memory for temporary arrays
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copy data to temp arrays
    for (std::size_t i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (std::size_t i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    std::size_t i = 0, j = 0, k = left;

    // Merge the temp arrays back into arr
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // Free the allocated memory for the temp arrays
    delete[] leftArr;
    delete[] rightArr;
}

void msort(int* arr, std::size_t left, std::size_t right, std::size_t ts) {
    if (right - left + 1 <= ts) {
        // Serial insertion sort
        std::cout << "Using serial sort: left = " << left << ", right = " << right << std::endl;
        for (std::size_t i = left + 1; i <= right; i++) {
            int key = arr[i];
            std::size_t j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    } else {
        std::size_t mid = left + (right - left) / 2;
        std::cout << "Splitting: left = " << left << ", mid = " << mid << ", right = " << right << std::endl;
        #pragma omp task shared(arr)
        msort(arr, left, mid, ts);
        #pragma omp task shared(arr)
        msort(arr, mid + 1, right, ts);
        #pragma omp taskwait
        merge(arr, left, mid, right);
    }
}
