#include <iostream>
#include <random>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include "convolution.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

	if (argc < 3) {
		cout << "Usage: " << argv[0] << " <n> <m>" << endl;
		return 1;
    	}

    	size_t n = atoi(argv[1]); 
    	size_t m = atoi(argv[2]); 

	random_device rd;
	mt19937_64 generator(rd());

	const float minImge = -10.0, maxImge = 10.0;
	const float minMask = -1.0, maxMask = 1.0;
	uniform_real_distribution<float> distImge(minImge, maxImge);
	uniform_real_distribution<float> distMask(minMask, maxMask); 

	float *image = new float[n*n];
	float *mask = new float[m*m];
	float *output = new float[n*n];

    	for (size_t i = 0; i < n; ++i) {
        	for (size_t j = 0; j < n; ++j) {
            		image[i * n + j] = distImge(generator);
        	}
    	}

    	for (size_t i = 0; i < m; ++i) {
        	for (size_t j = 0; j < m; ++j) {
            		mask[i * m + j] = distMask(generator);
        	}
    	}

    	auto start = high_resolution_clock::now();
    	convolve(image, output, n, mask, m); 
    	auto stop = high_resolution_clock::now();

	auto duration_ms = duration_cast<duration<double, std::milli>>(stop - start);

	cout << duration_ms.count() << endl;
	cout << output[0] << endl;
	cout << output[n-1] << endl;

	delete[] image;
	delete[] mask;
	delete[] output;

	return 0;
}
