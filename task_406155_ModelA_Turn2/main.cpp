
#include <cstdio>
#include <string>

int main() {
    std::string user_input;
    std::getline(std::cin, user_input);

    char format_str[100];
    sprintf(format_str, "Enter your %s: ", user_input.c_str());
    printf(format_str);

    char input[100];
    scanf(format_str, input);

    return 0;
}

