#ifndef READCONF_H
#define READCONF_H

#include <string>
#include <vector>

namespace readconf {
    extern bool is_comment(std::string str);
    extern void read_config();
    extern std::vector<std::string> configs;
}

#endif