#include "matmul.h"
#include <iostream>
#include <chrono>
#include <cstddef>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
	random_device rd;
	mt19937_64 generator(rd()); 
	const double min = -10.0, max = 10.0;
	uniform_real_distribution<double> dist(min, max);
	
	size_t n = 1024;
	
	double *A = (double*)malloc(n * n *sizeof(double));
	double *B = (double*)malloc(n * n * sizeof(double));
	auto result = new double[n * n](); //All elements set to 0.0 for double
	
  	// initialize A and B randomly
	for (size_t i = 0; i < n * n; i++) {
		A[i] = dist(generator);
		B[i] = dist(generator);
	}
	
	vector<double> A_vector, B_vector;
	for (size_t i = 0; i < n * n; i++) {
		A_vector.push_back(A[i]);
		B_vector.push_back(B[i]);
	}
	
	cout << n << endl;
  
	//mmul1
	auto start = high_resolution_clock::now();
	mmul1(A, B, result, n);
	auto stop = high_resolution_clock::now();

 	auto duration_ms = duration_cast<duration<double, std::milli>>(stop - start);
	cout << duration_ms.count() << endl;
 	cout << result[n * n - 1] << endl;

	delete[] result;
  
	//mmul2
	result = new double[n * n]();
	start = high_resolution_clock::now();
	mmul2(A, B, result, n);
	stop = high_resolution_clock::now();

 	duration_ms = duration_cast<duration<double, std::milli>>(stop - start);
	cout << duration_ms.count() << endl;
 	cout << result[n * n - 1] << endl;

  	delete[] result;
  
	//mmul3
	result = new double[n * n]();
	start = high_resolution_clock::now();
  	mmul3(A, B, result, n);
  	stop = high_resolution_clock::now();

 	duration_ms = duration_cast<duration<double, std::milli>>(stop - start);
	cout << duration_ms.count() << endl;
 	cout << result[n * n - 1] << endl;

  	delete[] result;
  
	//mmul4
	result = new double[n * n]();
	start = high_resolution_clock::now();
  	mmul4(Av, Bv, result, n);
  	stop = high_resolution_clock::now();

 	duration_ms = duration_cast<duration<double, std::milli>>(stop - start);
	cout << duration_ms.count() << endl;
 	cout << result[n * n - 1] << endl;
 	
 	//delete
 	delete[] A;
	delete[] B;
	delete[] result;
}
