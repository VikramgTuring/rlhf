
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstddef>

// Simple RLE compression
void rleCompress(const char* input, std::vector<char>& output) {
    char current = input[0];
    int count = 1;
    size_t outPos = 0;

    for (size_t inPos = 1; inPos < strlen(input); ++inPos) {
        if (input[inPos] == current) {
            ++count;
        } else {
            output.push_back(current);
            if (count > 1) {
                for (int i = 0; i < count; ++i) {
                    output.push_back('0' + count % 10);
                    count /= 10;
                }
            }
            current = input[inPos];
            count = 1;
        }
    }

    output.push_back(current);
    if (count > 1) {
        for (int i = 0; i < count; ++i) {
            output.push_back('0' + count % 10);
            count /= 10;
        }
    }
}

// Implement memory allocation using 'new'
void rleCompressWithNew(const char* input, char** output, size_t* outputSize) {
    char current = input[0];
    int count = 1;
    size_t outPos = 0;

    *outputSize = strlen(input) + 1; // +1 for null terminator 
    *output = new char[*outputSize];

    for (size_t inPos = 1; inPos < strlen(input); ++inPos) {
        if (input[inPos] == current) {
            ++count;
        } else {
            (*output)[outPos] = current;
            outPos++;
            if (count > 1) {
                for (int i = 0; i < count; ++i) {
                    (*output)[outPos] = '0' + count % 10;
                    count /= 10;
                    outPos++;
                }
            }
            current = input[inPos];
            count = 1;
        }
    }
    (*output)[outPos] = current;
    if (count > 1) {
        for (int i = 0; i < count; ++i) {
            (*output)[outPos+i+1] = '0' + count % 10;
            count /= 10;
        }
    }
    (*output)[outPos + count + 1] = '\0';
}

void measurePerformance(const char* data, const char* functionName) {
    std::vector<char> compressedVector;
    size_t outputSize = 0;
    char* compressedNew = nullptr;

    {
        auto start = std::chrono::high_resolution_clock::now();
        rleCompress(data, compressedVector);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Performance of " << functionName << " using std::vector: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }

    {
        auto start = std::chrono::high_resolution_clock::now(); 
        rleCompressWithNew(data, &compressedNew, &outputSize);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Performance of " << functionName << " using new: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
        delete[] compressedNew;
    }
}

int main() {
    const char* data = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";

    measurePerformance(data, "RLE compression");

    return 0;
}

