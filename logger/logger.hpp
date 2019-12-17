#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>

namespace logger {
    void init_logger(const std::string& file_name);
    void write_log(const std::string& log);
}

#endif  // LOGGER_H_
