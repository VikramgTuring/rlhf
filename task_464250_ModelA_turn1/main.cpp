#include <iostream>
#include <cstdio>

class PredictiveAlgorithm {
public:
    void runAlgorithm(int input) {
        // Log the input value
        printf("INFO: Running algorithm with input: %d\n", input);
        
        // Validate input
        if (input < 0) {
            printf("ERROR: Input cannot be negative. Received: %d\n", input);
            return; // Exit if the input is invalid
        }
        
        // Document assumptions
        printf("INFO: Assumption - Input is non-negative.\n");
        
        // Perform some calculation (for demonstration)
        int result = performCalculation(input);
        
        // Log the result of the calculation
        printf("INFO: Calculation result for input %d is: %d\n", input, result);
        
        // Check for specific conditions
        if (result > 100) {
            printf("WARNING: Result is unusually high: %d\n", result);
        }
    }

private:
    int performCalculation(int input) {
        // Just a simple calculation for illustration
        printf("DEBUG: Performing calculation with input: %d\n", input);
        return input * 2; // Example calculation
    }
};

int main() {
    PredictiveAlgorithm algorithm;
    
    // Test with various inputs
    algorithm.runAlgorithm(50);
    algorithm.runAlgorithm(-10);
    algorithm.runAlgorithm(75);
    
    return 0;
}
