#ifndef READCONF_H
#define READCONF_H

#define value_true value == "true"

#include <string>
#include <vector>

namespace readconf {
    bool is_comment(std::string str);
    void read_config();
    extern std::vector<std::string> configs;
}

#endif