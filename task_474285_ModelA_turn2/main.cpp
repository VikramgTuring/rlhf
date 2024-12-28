#include <iostream>
#include <vector>
#include <concepts>
#include <stdexcept>

// Concept to ensure the type is an arithmetic type
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// Function to process a matrix based on a dynamic runtime condition
template <Arithmetic T>
void processMatrix(const std::vector<std::vector<T>>& matrix, double multiplier) {
    // Ensure the multiplier is valid for the operation
    if (multiplier <= 0) {
        throw std::invalid_argument("Multiplier must be greater than zero.");
    }

    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Apply the dynamic condition (scaling the matrix element)
            T scaledValue = matrix[i][j] * static_cast<T>(multiplier);
            std::cout << "Scaled value: " << scaledValue << std::endl;
        }
    }
}

int main() {
    std::vector<std::vector<int>> intMatrix = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> doubleMatrix = {{1.5, 2.5}, {3.5, 4.5}};

    double multiplier = 2.0; // This could come from user input or another source

    std::cout << "Processing integer matrix with multiplier:" << multiplier << std::endl;
    processMatrix(intMatrix, multiplier);

    std::cout << "Processing double matrix with multiplier:" << multiplier << std::endl;
    processMatrix(doubleMatrix, multiplier);

    return 0;
}
