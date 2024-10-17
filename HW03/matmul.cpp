#include "matmul.h"
#include <omp.h> // Include OpenMP header
#include <iostream>

void mmul(const double *A, const double *B, double *C, const unsigned int n) {
    unsigned int i, j, k;
    
    // Parallelizing the outer loop with OpenMP
    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++) {
            for (j = 0; j < n; j++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}
