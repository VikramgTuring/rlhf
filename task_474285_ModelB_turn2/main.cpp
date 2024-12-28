#include <iostream>
#include <vector>
#include <concepts>

enum class Mode {
    SUM,
    PRODUCT
};

template <>
concept SumMode = Mode::SUM == Mode::SUM;

template <>
concept ProductMode = Mode::PRODUCT == Mode::PRODUCT;

template <typename T, typename ModeConcept>
requires ModeConcept
void processMatrix(const std::vector<std::vector<T>>& matrix, Mode mode) {
    static_assert(std::is_same_v<ModeConcept, std::bool_constant<Mode::SUM == mode>>, "Invalid mode selected");

    const T initValue = 0;
    T result = initValue;

    for (const auto& row : matrix) {
        for (const auto& element : row) {
            if constexpr (Mode::SUM == mode) {
                result += element;
            } else {
                result *= element;
            }
        }
    }
    std::cout << "Result: " << result << std::endl;
}

int main() {
    constexpr Mode mode = Mode::SUM; // Set the mode dynamically at compile-time based on runtime logic
    std::vector<std::vector<double>> matrix = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};

    if (mode == Mode::SUM) {
        std::cout << "Performing sum..." << std::endl;
        processMatrix<double, SumMode>(matrix, mode);
    } else if (mode == Mode::PRODUCT) {
        std::cout << "Performing product..." << std::endl;
        processMatrix<double, ProductMode>(matrix, mode);
    } else {
        std::cerr << "Invalid mode!" << std::endl;
        return 1;
    }

    return 0;
}
