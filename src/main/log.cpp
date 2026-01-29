#include <iostream>
#include <vector>

#include "../../include/main/log.h"

void Log::log(std::string message, bool print){
    Log::logs.push_back(message);
    if(print){
        std::cout << "[LOG] " << message << "\n";
    } 
}

std::vector<std::string> Log::logs = { };