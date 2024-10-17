#include <iostream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <omp.h>
#include "msort.h"

using namespace std;
using namespace chrono;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <n> <t> <ts>" << endl;
        return 1;
    }
    
    size_t n = atoi(argv[1]);  
    int num_threads = atoi(argv[2]);  
    size_t ts = atoi(argv[3]); 

    omp_set_num_threads(num_threads);

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(-1000, 1000);

    int* arr = new int[n];

    for (size_t i = 0; i < n; ++i) {
        arr[i] = dist(generator);
    }

    auto start = high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        msort(arr, 0, n - 1, ts);  // Sort the array
    }
    auto stop = high_resolution_clock::now();

    auto duration_ms = duration_cast<duration<double, milli>>(stop - start);

    cout << arr[0] << endl;
    cout << arr[n - 1] << endl;
    cout << duration_ms.count() << endl;

    delete[] arr;

    return 0;
}
