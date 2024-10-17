#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include "matmul.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <matrix_size> <num_threads>" << std::endl;
        return 1;
    }

    unsigned int n = std::atoi(argv[1]); // Size of the matrices
    int t = std::atoi(argv[2]);          // Number of threads

    // Initialize matrices A, B, and C (all of size n * n)
    std::vector<double> A(n * n), B(n * n), C(n * n, 0.0);

    // Fill matrices A and B with random float numbers
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed for random number generation
    for (unsigned int i = 0; i < n * n; i++) {
        A[i] = static_cast<double>(rand()) / RAND_MAX;
        B[i] = static_cast<double>(rand()) / RAND_MAX;
    }

    // Set the number of threads
    omp_set_num_threads(t);

    // Measure the time taken by the mmul function
    double start_time = omp_get_wtime();
    mmul(A.data(), B.data(), C.data(), n); // Parallel matrix multiplication
    double end_time = omp_get_wtime();

    // Calculate the elapsed time in milliseconds
    double elapsed_time_ms = (end_time - start_time) * 1000.0;

    // Print the first and last element of matrix C
    std::cout << "First element of C: " << C[0] << std::endl;
    std::cout << "Last element of C: " << C[n * n - 1] << std::endl;

    // Print the time taken in milliseconds
    std::cout << "Time taken by mmul: " << elapsed_time_ms << " milliseconds" << std::endl;

    return 0;
}
