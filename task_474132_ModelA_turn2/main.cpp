#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <iostream>
#include <string>

namespace logging = boost::log;
namespace src = boost::log::sources;

void init_logging() {
    logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
    logging::add_console_log(std::cout, logging::keywords::format = "[%TimeStamp%] [%Severity%]: %Message%");
    logging::add_common_attributes();
}

// Logger utility macros
#define LOG_INFO(msg) BOOST_LOG_TRIVIAL(info) << msg
#define LOG_WARN(msg) BOOST_LOG_TRIVIAL(warning) << msg
#define LOG_ERROR(msg) BOOST_LOG_TRIVIAL(error) << msg
#define LOG_DEBUG(msg) BOOST_LOG_TRIVIAL(debug) << msg

void log_packet_transmission(const std::string& packetData) {
    LOG_INFO("Transmitting packet: " << packetData);
}

void log_parsing_error(int errorCode) {
    LOG_ERROR("Parsing error occurred with error code: " << errorCode);
}

void log_connection_status(const std::string& statusMessage) {
    if (statusMessage == "connected") {
        LOG_INFO("Connection established: " << statusMessage);
    } else if (statusMessage == "disconnected") {
        LOG_WARN("Connection lost: " << statusMessage);
    } else {
        LOG_ERROR("Unknown connection status: " << statusMessage);
    }
}

int main() {
    // Initialize logging
    init_logging();

    // Simulate some network events for demonstration
    log_connection_status("connected");
    log_packet_transmission("Packet data 123456");
    log_parsing_error(404);
    log_connection_status("disconnected");
    log_packet_transmission("Packet data 789012");

    return 0;
}
