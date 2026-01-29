#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <filesystem>

#include "../../include/main/readconf.h"
#include "../../include/main/vars.h"
#include "../../include/main/os.h"
#include "../../include/main/log.h"
#include "../../include/main/configvars.h"

namespace fs = std::filesystem;

bool readconf::is_comment(std::string str)
{
    if (str.find(";") != std::string::npos) // does not have the comment line
    {
        return false;
    }
    else
    {
        return true;
    }
}

void readconf::read_config()
{
    os OS;
    OS = detect_os();
    
    Log::log("Detected OS", true);

    fs::path path = { };

    error_code = 0;
    status_code = 0;

    if (minimum)
    {
        Log::log("Minimum boolean set to true", true);
        return;
    }

    if (OS == lnx)
    {
        path = fs::path(std::getenv("HOME")) / ".config/libreterminal/config.conf";
        Log::log("Linux Detected on configuration", false);
    }
    else if (OS == win)
    {
        path = fs::path("C:\\LibreTerminal\\config.conf");
        Log::log("Windows Detected on configuration", false);
    }
    else
    {
        Log::log("ERROR 005 - CANNOT CONTINUE", true);
        error_code = 5;
        status_code = 1;
        exit(error_code);
    }

    std::cout << path;
    std::fstream config_f(path);

    std::string text = { };
    
    if (fs::exists(path))
    {
        Log::log("Path exists", true);
        
        if(!config_f){
            std::cout << "test-error\n";
        }
        
        Log::log("About to read from configuration", false);
        
            
        while (std::getline(config_f, text))
        {
           Log::log(text, false); 
        }
        Log::log("Stopped reading from configuration", false);
    }
    else
    {
        error_code = 3;
        status_code = 1;
        Log::log("ERROR 003 - CANNOT CONTINUE", true);
        exit(error_code);
    }
}
