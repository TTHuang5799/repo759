#include "msort.h"
#include <omp.h>
#include <iostream>

// Function to merge two halves of the array
void merge(int* arr, std::size_t left, std::size_t mid, std::size_t right) {
    std::size_t n1 = mid - left + 1;
    std::size_t n2 = right - mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copy data to temporary arrays
    for (std::size_t i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (std::size_t i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    std::size_t i = 0, j = 0, k = left;

    // Merge the two halves
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

    // Copy remaining elements
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

// Recursive merge sort function
void msort(int* arr, std::size_t left, std::size_t right) {
    if (left < right) {
        std::size_t mid = left + (right - left) / 2;

        // Parallelize the sorting of the two halves using OpenMP
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                msort(arr, left, mid);  // Sort the first half
            }
            #pragma omp section
            {
                msort(arr, mid + 1, right);  // Sort the second half
            }
        }

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}
