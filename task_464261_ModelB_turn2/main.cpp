#include <cstring>

struct Device {
    char model[32];
    char firmware[16];
};

void initDevice(Device* device) {
    strcpy(device->model, "XYZ-123");
    strcpy(device->firmware, "V1.0.2");
}

int main() {
    Device device;
    initDevice(&device);

    size_t modelLen = strlen(device.model);
    size_t firmwareLen = strlen(device.firmware);

    printf("Device Model: %s (Length: %zu)\n", device.model, modelLen);
    printf("Device Firmware: %s (Length: %zu)\n", device.firmware, firmwareLen);

    return 0;
}
