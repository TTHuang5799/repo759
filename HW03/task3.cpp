#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>
#include "msort.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " n t ts\n";
        return 1;
    }

    int n = std::stoi(argv[1]);  // Array size
    int t = std::stoi(argv[2]);  // Number of threads
    int ts = std::stoi(argv[3]); // Threshold

    // Set the number of threads
    omp_set_num_threads(t);

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1000, 1000);

    // Create and fill the array
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }

    // Time the sorting process
    auto start = std::chrono::high_resolution_clock::now();
    msort(arr, n, ts);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Print the first and last elements
    std::cout << arr[0] << std::endl;
    std::cout << arr[n - 1] << std::endl;

    // Print the time taken
    std::cout << elapsed.count() << " ms\n";

    delete[] arr;
    return 0;
}
