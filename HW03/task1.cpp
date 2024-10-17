#include "matmul.h"
#include <iostream>
#include <chrono>
#include <cstddef>
#include <random>
#include <omp.h>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <matrix_size> <num_threads>" << endl;
        return 1;
    }

    // Initialize random number generator and distribution
    random_device rd;
    mt19937_64 generator(rd()); 
    const double min = -10.0, max = 10.0;
    uniform_real_distribution<double> dist(min, max);
    
    size_t n = atoi(argv[1]);  // Matrix size
    int num_threads = atoi(argv[2]);  // Number of threads

    // Allocate memory for matrices A, B, and result C
    double *A = new double[n * n];
    double *B = new double[n * n]; 
    auto C = new double[n * n]();  // Initialize result matrix C to 0.0

    // Initialize A and B with random values
    for (size_t i = 0; i < n * n; i++) {
        A[i] = dist(generator);
        B[i] = dist(generator);
    }

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Measure time for parallel mmul (matrix multiplication)
    auto start = high_resolution_clock::now();
    mmul(A, B, C, n);  // Parallelized matrix multiplication with OpenMP
    auto stop = high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration_ms = duration_cast<duration<double, milli>>(stop - start);

    // Print first and last elements of the result matrix C
    cout << C[0] << endl;
    cout << C[n * n - 1] << endl;
    cout << duration_ms.count() << endl;

    // Clean up dynamically allocated memory
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
