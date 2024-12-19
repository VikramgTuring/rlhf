#include <cstdio>
#include <vector>
using namespace std;

int main() {
   // Function to predict output based on a simple linear model
   double predict(double x, double slope, double intercept) {
       // Assumption: x, slope, and intercept are finite numbers
       if (!isfinite(x) || !isfinite(slope) || !isfinite(intercept)) {
           printf("Assertion Error: x, slope, and intercept should be finite numbers.\n");
           exit(EXIT_FAILURE);
       }

       double prediction = slope * x + intercept;
       return prediction;
   }
   //Function to perform prediction on a dataset
   void runPrediction(){
       // Validation: Ensure we have non-zero training data points
       vector<double> input_data = {1.0, 2.0, 3.0, 4.0};
       vector<double> output_data = {2.0, 5.0, 8.0, 11.0};

       if (input_data.size() != output_data.size() || input_data.empty()) {
           printf("Validation Error: Training data should be non-empty and have the same size for input and output.\n");
           exit(EXIT_FAILURE);
       }
       double slope = 3.0; // Assume some trained slope
       double intercept = -1.0; // Assume some trained intercept

       double prediction = predict(5.0, slope, intercept);
       printf("Prediction for x=5.0: %lf\n", prediction);

       // Assume some validation data
       double validation_x = 6.0;
       double validation_expected_output = 17.0;

       // Validation: Predict the output for validation data and compare with the expected result
       double validation_prediction = predict(validation_x, slope, intercept);
       printf("Validation Prediction for x=%lf: %lf\n", validation_x, validation_prediction);
       if (fabs(validation_prediction - validation_expected_output) > 0.0001) {
           printf("Validation Error: Prediction for validation data does not match expected output.\n");
           exit(EXIT_FAILURE);
       } else {
           printf("Validation passed.\n");
       }
   }
  runPrediction();
   return 0;
}
