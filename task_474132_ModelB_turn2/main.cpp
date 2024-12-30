// Enumerate network event severities
namespace net_severity {
    enum type : int {
        trace      = boost::log::trivial::trace,
        debug      = boost::log::trivial::debug,
        info       = boost::log::trivial::info,
        warning    = boost::log::trivial::warning,
        error      = boost::log::trivial::error,
        critical   = boost::log::trivial::fatal
    };

    inline std::ostream& operator<<(std::ostream& os, type severity) {
        switch (severity) {
            case trace:      return os << "TRACE";
            case debug:      return os << "DEBUG";
            case info:       return os << "INFO";
            case warning:    return os << "WARNING";
            case error:      return os << "ERROR";
            case critical:   return os << "CRITICAL";
        }
        return os;
    }
}

// Source location attributes and sink
BOOST_LOG_GLOBAL_LOGGER(network_logger, src::severity_logger<net_severity::type>)

void init_network_logging() {
    logging::core::get()->set_filter(logging::trivial::severity >= net_severity::trace);
    auto console_sink = logging::add_console_log(std::cout,
                                                logging::keywords::format =
                                                "[%TimeStamp%] [%Severity%]: [%SourceLineFunction%]: %Message%");
    logging::add_common_attributes();

    // Configure additional filter on the sink if needed
    console_sink->set_filter(logging::trivial::severity >= net_severity::info);
}

// Logger utilities for network events
#define NETLOG_TRACE(msg)   BOOST_LOG_SEVERITY(*network_logger, net_severity::trace) << msg
#define NETLOG_DEBUG(msg)   BOOST_LOG_SEVERITY(*network_logger, net_severity::debug) << msg
#define NETLOG_INFO(msg)     BOOST_LOG_SEVERITY(*network_logger, net_severity::info) << msg
#define NETLOG_WARNING(msg)   BOOST_LOG_SEVERITY(*network_logger, net_severity::warning) << msg
#define NETLOG_ERROR(msg)     BOOST_LOG_SEVERITY(*network_logger, net_severity::error) << msg
#define NETLOG_CRITICAL(msg) BOOST_LOG_SEVERITY(*network_logger, net_severity::critical) << msg

// Example functions
void handle_packet_transmission() {
    NETLOG_INFO("Packet transmitted successfully.");
}

void parse_packet() {
    try {
        // Some parsing logic
        NETLOG_DEBUG("Packet parsed successfully.");
    } catch (...) {
        NETLOG_ERROR("Error parsing packet: %s", logging::expressions::error_info_as_string().c_str());
    }
}

void connection_established() {
    NETLOG_INFO("Connection established.");
}

void connection_lost() {
    NETLOG_WARNING("Connection lost.");
}

int main() {
    init_network_logging();

    handle_packet_transmission();
    parse_packet();
    connection_established();
    connection_lost();

    return 0;
}
