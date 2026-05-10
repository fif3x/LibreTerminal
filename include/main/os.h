#ifndef OS_H
#define OS_H

#include <string>

#ifndef lnx
#define lnx os::LINUX
#endif

#ifndef win
#define win os::WIN
#endif

#ifndef unk
#define unk os::UNKN
#endif

enum os
{
    WIN,
    LINUX,
    UNKN
};

inline os detect_os()
{
#if defined(_WIN32) || defined(_WIN64)
    return os::WIN;
#elif defined(__linux__)
    return os::LINUX;
#else
    return os::UNKN;
#endif
}

extern void print_os();
extern std::string get_username();
extern std::string get_hostname();
extern std::string get_log_path();

#endif