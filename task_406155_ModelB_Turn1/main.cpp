
#include <iostream>
#include <string>
#include <regex>

void findFormatStringVulnerabilities(const std::string& code) {
    std::regex formatStringRegex(
        R"(\b(printf|scanf|sprintf|fprintf|snprintf|vprintf|vscanf|vsprintf|vfprintf|vsnprintf)\s*\([^\)]*%[^)]*\))"
    );

    std::smatch match;
    while (std::regex_search(code, match, formatStringRegex)) {
        std::cout << "Potential format string vulnerability found:\n"
                 << "Code snippet: '" << match.str() << "'\n"
                 << "Line number (not available in this basic example): <line number>\n\n";

        code = match.suffix().str();
    }
}

int main() {
    std::string code_snippet_1 = R"(
    void some_function() {
        char buffer[100];
        printf("Invalid format: %u\n", buffer); // Potential vulnerability
        scanf("%s", buffer);   // Potential vulnerability
    }
    )";

    std::string code_snippet_2 = R"(
    void another_function() {
        int result;
        printf("Result: %d\n", result);  // Should not be flagged
        scanf("%d", &result);  // Should not be flagged
    }
    )";    
    std::cout << "Analysing code snippet 1:\n";
    findFormatStringVulnerabilities(code_snippet_1);

    std::cout << "\nAnalysing code snippet 2:\n";
    findFormatStringVulnerabilities(code_snippet_2);

    return 0;
}

 
