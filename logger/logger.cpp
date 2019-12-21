#define BOOST_LOG_DYN_LINK 1

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "logger.hpp"

void logger::init_logger(const std::string& file_name) {
    boost::log::add_file_log(
        boost::log::keywords::file_name = file_name,
        boost::log::keywords::format = "[%TimeStamp%] %Message%"
    );
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= boost::log::trivial::info
    );
    boost::log::add_common_attributes();
}

void logger::write_trace(const std::string& log) {
    BOOST_LOG_TRIVIAL(trace) << log;
}

void logger::write_debug(const std::string& log) {
    BOOST_LOG_TRIVIAL(debug) << log;
}

void logger::write_info(const std::string& log) {
    BOOST_LOG_TRIVIAL(info) << log;
}

