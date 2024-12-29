#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions.hpp>
#include <iostream>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

void init_logging() {
    logging::add_console_log(
        std::cout,
        keywords::format = "[%TimeStamp%] [%Severity%]: %Message%"
    );
    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info
    );
    logging::add_common_attributes();
}

// Logger utility macros
#define LOG_INFO(msg) BOOST_LOG_TRIVIAL(info) << msg
#define LOG_WARN(msg) BOOST_LOG_TRIVIAL(warning) << msg
#define LOG_ERROR(msg) BOOST_LOG_TRIVIAL(error) << msg

// Example function
void example_function() {
    LOG_INFO("Starting example_function...");

    // Some operation...
    int result = 42; // Dummy operation
    if (result < 0) {
        LOG_ERROR("An error occurred: Result is negative!");
    }
    else {
        LOG_INFO("Result is: " << result);
    }

    // More Boost.Log usage
    LOG_WARN("This is a warning message from Boost.Log");
}

int main() {
    init_logging(); // Initialize logging

    example_function(); // Call example function

    return 0;
}

