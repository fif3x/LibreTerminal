#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>
#include <iostream>

template<typename T>
void dbg(const T &var, const std::string &name){
    std::cout << "Value: " << var << " Address: " << &var << " Name:" << name << std::endl;
}

#endif