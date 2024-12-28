#include <iostream>
#include <vector>
#include <concepts>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
void processMatrix(const std::vector<std::vector<T>>& matrix) {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Perform operation on arithmetic types
            std::cout << "Processing: " << (matrix[i][j] * matrix[i][j]) << std::endl; // Example operation
        }
    }
}

template <>
void processMatrix<double>(const std::vector<std::vector<double>>& matrix) {
    // Specific optimization or alternative operation for doubles
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            // Optimized operation for double (e.g., using a faster algorithm)
            std::cout << "Processing double: " << (matrix[i][j]) << std::endl;
        }
    }
}

int main() {
    std::vector<std::vector<int>> intMatrix = {{1, 2}, {3, 4}};
    std::vector<std::vector<double>> doubleMatrix = {{1.5, 2.5}, {3.5, 4.5}};

    std::cout << "Processing integer matrix:" << std::endl;
    processMatrix(intMatrix);

    std::cout << "Processing double matrix:" << std::endl;
    processMatrix(doubleMatrix);

    return 0;
}
