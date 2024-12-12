#include <iostream>

class SensorData {
public:
    SensorData(int temperature, float humidity) : temp(temperature), hum(humidity) {}
    ~SensorData() { }  // Destructor to free any resources (if needed)

    int temp;
    float hum;
};

// Function to read sensor data (simulated)
SensorData* readSensor() {
    int temp = 25;
    float hum = 60.5f;
    return new SensorData(temp, hum);  // Dynamically allocate memory
}

int main() {
    // Using 'new' directly (not recommended in embedded systems)
    SensorData* sensorData = readSensor();

    if (sensorData) {
        // Use the sensor data
        std::cout << "Temperature: " << sensorData->temp << "°C" << ", Humidity: " << sensorData->hum << "%" << std::endl;

        // Deallocate the memory manually
        delete sensorData;
    } else {
        std::cout << "Memory allocation failed!" << std::endl;
    }

    // Better approach: Using std::unique_ptr (recommended for modern C++)
    {
        std::unique_ptr<SensorData> sensorDataPtr(readSensor());

        if (sensorDataPtr) {
            std::cout << "Temperature: " << sensorDataPtr->temp << "°C" << ", Humidity: " << sensorDataPtr->hum << "%" << std::endl;
        } else {
            std::cout << "Memory allocation failed!" << std::endl;
        }
    }

    return 0;
}
