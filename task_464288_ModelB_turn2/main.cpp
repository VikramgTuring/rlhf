#include <iostream>
#include <vector>

class SimpleContainer {
public:
    int value;
    SimpleContainer() : value(0) {}

    // Deep copy constructor
    SimpleContainer(const SimpleContainer& other) : value(other.value) {}

    // Deep copy assignment operator
    SimpleContainer& operator=(const SimpleContainer& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }
};

class ComplexData {
public:
    int data1;
    SimpleContainer* data2;
    std::vector<int> data3;

    ComplexData() : data1(0), data2(nullptr) {
        data3.push_back(1);
        data3.push_back(2);
    }

    // Deep copy constructor
    ComplexData(const ComplexData& other) {
        data1 = other.data1;
        if (other.data2 != nullptr) {
            data2 = new SimpleContainer(*other.data2);  // Deep copy of data2
        } else {
            data2 = nullptr;
        }
        data3 = other.data3;  // std::vector does a deep copy automatically
    }

    // Deep copy assignment operator
    ComplexData& operator=(const ComplexData& other) {
        if (this != &other) {
            data1 = other.data1;
            if (data2 != nullptr) {
                delete data2;  // Delete old data2
            }
            if (other.data2 != nullptr) {
                data2 = new SimpleContainer(*other.data2);
            } else {
                data2 = nullptr;
            }
            data3 = other.data3;
        }
        return *this;
    }

    ~ComplexData() {
        delete data2;  // Remember to delete dynamically allocated memory
    }
};

template <typename T>
T* cloneArray(const T* arr, size_t size) {
    T* clonedArray = new T[size];
    for (size_t i = 0; i < size; i++) {
        clonedArray[i] = arr[i];
    }
    return clonedArray;
}

int main() {
    ComplexData data1;
    data1.data1 = 10;
    data1.data2 = new SimpleContainer;
    data1.data2->value = 20;

    ComplexData arr[] = { data1, { 20, nullptr } };
    size_t size = sizeof(arr) / sizeof(arr[0]);

    ComplexData* clonedArray = cloneArray(arr, size);

    for (size_t i = 0; i < size; i++) {
        std::cout << "Cloned array element " << i << ": data1 = " << clonedArray[i].data1 << ", ";
        if (clonedArray[i].data2 != nullptr) {
            std::cout << "data2->value = " << clonedArray[i].data2->value << ", ";
        } else {
            std::cout << "data2 = nullptr, ";
        }
        for (const int& val : clonedArray[i].data3) {
            std::cout << "data3.val = " << val << ", ";
        }
        std::cout << "\n";
    }

    // Always delete the dynamically allocated memory
    delete[] clonedArray;

    return 0;
}
