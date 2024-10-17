#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <omp.h>
#include "msort.h"

using namespace std;
using namespace chrono;

// Insertion sort function for small subarrays
void insertion_sort(int* arr, std::size_t left, std::size_t right) {
    for (size_t i = left + 1; i <= right; i++) {
        int key = arr[i];
        std::size_t j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Modified merge sort with threshold for switching to serial sorting
void msort_threshold(int* arr, std::size_t left, std::size_t right, std::size_t ts) {
    if (right - left + 1 <= ts) {
        // Use insertion sort if below threshold
        insertion_sort(arr, left, right);
    } else {
        // Use parallel msort from msort.cpp for larger arrays
        msort(arr, left, right);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <n> <t> <ts>" << endl;
        return 1;
    }

    size_t n = atoi(argv[1]);  
    int num_threads = atoi(argv[2]);  
    size_t ts = atoi(argv[3]);  

    omp_set_num_threads(num_threads);

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(-1000, 1000);

    // Allocate memory for the array
    int* arr = new int[n];

    // Fill the array with random values
    for (size_t i = 0; i < n; ++i) {
        arr[i] = dist(generator);
    }

    auto start = high_resolution_clock::now();
    msort_threshold(arr, 0, n - 1, ts);  // Sort with the threshold
    auto stop = high_resolution_clock::now();

    auto duration_ms = duration_cast<duration<double, milli>>(stop - start);

    cout << arr[0] << endl;
    cout << arr[n - 1] << endl;
    cout << duration_ms.count() << endl;

    delete[] arr;

    return 0;
}
