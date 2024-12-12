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
                    output.push_back('0' + (count % 10));
                    count /= 10;
                }
            }
            current = input[inPos];
            count = 1;
        }
    }

    // Output the last run
    output.push_back(current);
    if (count > 1) {
        for (int i = 0; i < count; ++i) {
            output.push_back('0' + (count % 10));
            count /= 10;
        }
    }
}

// Time measurement function
template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return double(duration.count()) / 1000.0; // Return milliseconds
}

int main() {
    const char* inputData = "WWWWWWWWWWWWBBBBBBBBBBBBRRRRRRRRRRRRGGRRRRRRRRRRRRGGRRRRRRRRRRRRGG";
    size_t inputSize = strlen(inputData);

    // Compression using std::vector (recommended)
    {
        std::vector<char> compressedData;
        double time = measureTime([&] {
            rleCompress(inputData, compressedData);
        });
        std::cout << "Compression using std::vector: " << time << " ms\n";
    }

    // Compression using raw new[] (manual memory management)
    {
        double time = measureTime([&] {
            char* compressedData = new char[inputSize * 2]; // Overestimate for simplicity
            rleCompress(inputData, compressedData);

            // Here you'd do something with the compressed data
            // For demonstration, we'll just resize it to the actual size
            size_t actualCompressedSize = compressedData - strlen(compressedData);
            char* finalCompressedData = new char[actualCompressedSize];
            std::memcpy(finalCompressedData, compressedData, actualCompressedSize);
            delete[] compressedData;
        });
        std::cout << "Compression using new[]: " << time << " ms\n";
    }

    return 0;
}
