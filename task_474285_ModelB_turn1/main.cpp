// Concept to check if a type is a numeric type
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

// Function template to sum elements of a matrix, with constraints on element type using the concept.
template <Numeric T>
constexpr T sumMatrixElements(const std::vector<std::vector<T>>& matrix) {
    T totalSum = 0;
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            totalSum += element;
        }
    }
    return totalSum;
}

int main() {
    // Example usage of the sumMatrixElements function with double precision floating point.
    std::vector<std::vector<double>> matrixDouble = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };

    double sumDouble = sumMatrixElements(matrixDouble);
    std::cout << "Sum of elements in the double matrix: " << sumDouble << std::endl;

    // Example usage with integer matrix.
    std::vector<std::vector<int>> matrixInt = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int sumInt = sumMatrixElements(matrixInt);
    std::cout << "Sum of elements in the integer matrix: " << sumInt << std::endl;

    return 0;
}
