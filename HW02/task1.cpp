#include "scan.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]){
	random_device rd;
	mt19937_64 generator(rd());
	const float min = -1.0, max = 1.0;
	uniform_real_distribution<float> dist(min, max);
	
	size_t n = atol(argv[1]);
	float *arr = (float*)malloc(n * sizeof(float));
	float *output = (float*)malloc(n * sizeof(float));

	for (size_t i = 0; i < n; i++){
		arr[i] = dist(generator);
	}
	
	auto start = high_resolution_clock::now();
	scan(arr, output, n);
	auto stop = high_resolution_clock::now();

	auto duration_sec = duration_cast<duration<double, std::milli>>(stop - start);
	cout << duration_sec.count() << endl;
	cout << output[0] << endl;
	cout << output[n-1] << endl;

	free(arr);
	free(output);
}
