#include "convolution.h"
#include <cstddef>
#include <omp.h>

float check_f(const float *f, std::size_t i, std::size_t j, std::size_t n) {
    if (0 <= i && i < n && 0 <= j && j < n) {
        return f[i * n + j];
    }
    if ((0 <= i && i < n) || (0 <= j && j < n)) {
        return 1;
    }
    return 0;
}

void convolve(const float *image, float *output, std::size_t n, const float *mask, std::size_t m) {
    // Initialize all output elements to 0
    for (std::size_t i = 0; i < n * n; i++) {
        output[i] = 0;
    }

    // Parallelize the outer two loops (x and y dimensions of the image)
    #pragma omp parallel for collapse(2)
    for (std::size_t x = 0; x < n; x++) {
        for (std::size_t y = 0; y < n; y++) {
            for (std::size_t i = 0; i < m; i++) {
                for (std::size_t j = 0; j < m; j++) {
                    // Apply the mask, accumulate the result
                    output[x * n + y] += mask[i * m + j] * check_f(image, x + i - ((m - 1) / 2), y + j - ((m - 1) / 2), n);
                }
            }
        }
    }
}
