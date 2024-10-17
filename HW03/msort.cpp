#include "msort.h"
#include <omp.h>
#include <iostream>

using namespace std;

// Function to merge two halves of the array
void merge(int* arr, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copy data to temporary arrays
    for (size_t i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (size_t i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    size_t i = 0, j = 0, k = left;

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
void msort(int* arr, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;

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
