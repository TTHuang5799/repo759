#ifndef MATMUL_H
#define MATMUL_H

#include <cstddef>
#include <vector>

using namespace std;

void mmul1(const double *A, const double *B, double *C, const unsigned int n);
void mmul2(const double *A, const double *B, double *C, const unsigned int n);
void mmul3(const double *A, const double *B, double *C, const unsigned int n);
void mmul4(const vector<double> &A, const vector<double> &B, double *C, const unsigned int n);

#endif
