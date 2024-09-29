#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "matplotlibcpp.h"  // Include matplotlib-cpp for plotting

namespace plt = matplotlibcpp;

int main() {
    std::vector<int> powers;
    std::vector<double> times;
    for (int i = 10; i <= 30; i++) {
        powers.push_back(i);
    }

    std::ifstream infile("task1.output");
    if (!infile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::string line;
    for (int i = 0; i < powers.size(); i++) {
        std::getline(infile, line);  // Skip 1st line
        std::getline(infile, line);  // Read the time value
        times.push_back(std::stod(line));  // Convert string to double and append to times
        std::getline(infile, line);  // Skip 3rd line
        std::getline(infile, line);  // Skip 4th line
        std::getline(infile, line);  // Skip 5th line
    }
    infile.close();

    plt::plot(powers, times, "o");
    plt::xlabel("Size of the array (power)");
    plt::ylabel("Time (milliseconds)");
    plt::title("Scaling Analysis Plot");

    plt::save("task1.pdf");

    return 0;
}

