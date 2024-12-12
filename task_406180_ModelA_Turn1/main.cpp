#include<stdio.h>
class SensorData {
public:
    float temperature;
    float humidity;

    SensorData(float temperature, float humidity) : temperature(temperature), humidity(humidity) {}
    ~SensorData() {
        printf("SensorData destructor called.\n");
    }
};

int main() {
    bool readingsAvailable = true;

    while (readingsAvailable) {
        SensorData* newReading = new SensorData(25.3, 60.5);  // Dynamic memory allocation

        // Use the data as needed
        processSensorData(*newReading);
        // ALWAYS remember to deallocate the memory!
        delete newReading;
        newReading = nullptr; 
    }

    return 0;
}
