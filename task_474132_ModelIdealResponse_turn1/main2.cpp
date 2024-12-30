#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#define BOOST_LOG_DYN_LINK
void init_logging() {
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info);
}

int main() {
    init_logging();
    BOOST_LOG_TRIVIAL(info) << "This is an info message";
    return 0;
}

