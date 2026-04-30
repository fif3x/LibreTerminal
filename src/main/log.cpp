#include <iostream>
#include <vector>
#include <fstream>

#include "../../include/main/log.h"
#include "../../include/main/configvars.h"
#include "../../include/main/os.h"

void Log::log(std::string message, bool print){
    Log::logs.push_back(message);
    if(print){
        std::cout << "[LOG] " << message << "\n";
    }

    if(config::save_logs_to_file){
        std::string path = get_log_path();
        std::ofstream file(path, std::ios::app); // std::ios::app so we dont overwrite already existing logs file
        if(!file){
            std::cerr << "Cannot open file " << path << "\n";
            exit(1);
        }

        file << message << "\n";
    }
}

std::vector<std::string> Log::logs = { };