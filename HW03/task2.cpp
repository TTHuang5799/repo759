#include <iostream>
#include <random>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <omp.h>  // OpenMP header
#include "convolution.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {

    // Check for the correct number of arguments
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <matrix_size> <num_threads>" << endl;
        return 1;
    }

    size_t n = atoi(argv[1]);  // Size of the image matrix
    int num_threads = atoi(argv[2]);  // Number of threads

    // Set the number of threads for OpenMP
    omp_set_num_threads(num_threads);

    // Random number generation
    random_device rd;
    mt19937_64 generator(rd());

    const float minImge = -10.0, maxImge = 10.0;
    const float minMask = -1.0, maxMask = 1.0;
    uniform_real_distribution<float> distImge(minImge, maxImge);
    uniform_real_distribution<float> distMask(minMask, maxMask);

    // Allocate memory for image, mask, and output
    float *image = new float[n * n];
    float *mask = new float[3 * 3];  // Fixed 3x3 mask
    float *output = new float[n * n];

    // Initialize image with random values
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            image[i * n + j] = distImge(generator);
        }
    }

    // Initialize 3x3 mask with random values
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            mask[i * 3 + j] = distMask(generator);
        }
    }

    auto start = high_resolution_clock::now();
    convolve(image, output, n, mask, 3);  // Apply 3x3 mask to image
    auto stop = high_resolution_clock::now();

    auto duration_ms = duration_cast<duration<double, std::milli>>(stop - start);

    cout << output[0] << endl;
    cout << output[n * n - 1] << endl;
    cout << duration_ms.count() << endl;

    delete[] image;
    delete[] mask;
    delete[] output;

    return 0;
}
