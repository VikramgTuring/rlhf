
#include <iostream>
#include <string>
#include <regex>

bool containsFormatStringVulnerability(const std::string& code) {
    std::regex format_string_regex(R"((scanf|printf|sprintf|fprintf|vsprintf|vfprintf)\s*\(\s*[^)]*%[^)]*\s*\))");
    std::smatch match;

    if (std::regex_search(code, match, format_string_regex)) {
        std::cout << "Format string vulnerability detected in the following code: \n" << code << std::endl;
        return true;
    }
    return false;
}

int main() {
    std::string code1 = "printf(\"Hello, %s!\", name); // Potentially vulnerable";
    std::string code2 = "int num; scanf(\"%d\", &num);";
    std::string code3 = "std::cout << \"Value: \" << value << std::endl;"; // Not vulnerable

    if (containsFormatStringVulnerability(code1)) {
        return 1;
    }
    
    if (containsFormatStringVulnerability(code2)) {
        return 1;
    }

    if (containsFormatStringVulnerability(code3)) {
        return 1;
    }
    std::cout << "No format string vulnerabilities found." << std::endl;
    return 0;
}
