#include <iostream>

const double PI = 3.14159;
const int MAX_LENGTH = 100;
const int ARRAY_SIZE = 5;

constexpr double PI_CONSTEXPR = 3.14159;
constexpr int MAX_LENGTH_CONSTEXPR = 100;
constexpr int ARRAY_SIZE_CONSTEXPR = 5;

int main() {
    // Usage of const variables
    std::cout << "PI: " << PI << std::endl;
    std::cout << "MAX_LENGTH: " << MAX_LENGTH << std::endl;
    char array[ARRAY_SIZE];

    // Usage of constexpr variables
    std::cout << "PI_CONSTEXPR: " << PI_CONSTEXPR << std::endl;
    std::cout << "MAX_LENGTH_CONSTEXPR: " << MAX_LENGTH_CONSTEXPR << std::endl;
    constexpr int num_elements = ARRAY_SIZE_CONSTEXPR * 2;
    char constexpr* constexpr_string = "constexpr string";

    return 0;
}
