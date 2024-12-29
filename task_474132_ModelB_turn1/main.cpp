#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <iostream>

// Boost.Log configuration
namespace logging = boost::log;
namespace sinks = logging::sinks;
namespace expr = logging::expressions;

void initialiseLogging() {
    auto consoleSink = sinks::make_text_ostream_backend("std::cerr");
    consoleSink->set_filter(logging::trivial::severity >= logging::trivial::info);
    logging::core::get()->add_backend(consoleSink);
}

// Function utilising Boost.Log
void processNetworkPacket(const void* data, size_t size) {
    BOOST_LOG_TRIVIAL(info) << "Received packet of size " << size;
}

// Function utilising printf
void debugMemoryAllocation() {
    void* ptr = malloc(1024);
    if (ptr) {
        printf("Allocated memory: %p\n", ptr);
        free(ptr);
    } else {
        printf("Memory allocation failed!\n");
    }
}

int main() {
    initialiseLogging();

    // Simulate packet processing
    processNetworkPacket(nullptr, 128);

    // Demonstrate printf for quick debugging
    debugMemoryAllocation();

    return 0;
}
