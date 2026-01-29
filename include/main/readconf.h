#ifndef READCONF_H
#define READCONF_H

#include <string>

namespace readconf {
    extern bool is_comment(std::string str);
    extern void read_config();
}

#endif