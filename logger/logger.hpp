#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace logger {
    void init_logger(const std::string& file_name);
    void write_trace(const std::string& log);
    void write_debug(const std::string& log);
    void write_info(const std::string& log);
}

#endif  // LOGGER_H_
