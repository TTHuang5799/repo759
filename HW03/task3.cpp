#include <iostream>
#include <random>
#include <chrono>
#include <omp.h>
#include "msort.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " n t ts\n";
        return 1;
    }

    int n = stoi(argv[1]); 
    int t = stoi(argv[2]);
    int ts = stoi(argv[3]);

    omp_set_num_threads(t);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(-1000, 1000);

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = dis(gen);
    }

    auto start = high_resolution_clock::now();
    msort(arr, 0, n - 1, ts); 
    auto end = high_resolution_clock::now();
    
    auto duration_ms = duration_cast<duration<double, milli>>(end - start);
    cout << arr[0] << endl;
    cout << arr[n - 1] << endl;
    cout << duration_ms.count() << endl;

    delete[] arr;
    return 0;
}
