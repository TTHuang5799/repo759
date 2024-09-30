#ifndef MATMUL_H
#define MATMUL_H

#include <cstddef>
#include <vector>

void mmul1(const double *A, const double *B, double *C, const unsigned int n);
void mmul2(const double *A, const double *B, double *C, const unsigned int n);
void mmul3(const double *A, const double *B, double *C, const unsigned int n);
void mmul4(const std::vector<double> &A, const std::vector<double> &B, double *C, const unsigned int n);

#endif
