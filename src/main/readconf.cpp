#include <fstream>
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <filesystem>
#include <map>
#include <algorithm>

#include "../../include/main/readconf.h"
#include "../../include/main/vars.h"
#include "../../include/main/os.h"
#include "../../include/main/log.h"
#include "../../include/main/configvars.h"

#define DEBUG_BUILD false

namespace fs = std::filesystem;

bool readconf::is_comment(std::string str)
{
    if (str.find("#") != std::string::npos) // does not have the comment line
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<std::string> readconf::configs = { };

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
        path = fs::path(std::getenv("APPDATA")) / "libreterminal/config.conf";
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
            std::cerr << "Config file does not exist\n";
        }

        if(DEBUG_BUILD){
            Log::log("Before reading config and pushing to `readconf::configs`", true);
        }

        while (std::getline(config_f, text))
        {
            if(!is_comment(text) && !(text.empty())){
                readconf::configs.push_back(text);
            }
        }
        
        for (int index = 0; index < readconf::configs.size(); index++){
            auto it = readconf::configs.at(index).find('=');
            std::string key = { };
            std::string value = { };


            if(DEBUG_BUILD){
                Log::log("Before splitting key and value", true);
            }

            if (it != std::string::npos) {
                key = readconf::configs.at(index).substr(0, it);
                value = readconf::configs.at(index).substr(it + 1);
            }

            if(DEBUG_BUILD){
                Log::log(std::string("`key`: " + key), true);
                Log::log(std::string("`value`: " + value), true);
            }

            if(key == "shell"){
                config::shell = value;
            } 
            else if (key == "auto_exec"){

                if(value_true) config::auto_exec = true;
                
            } else if (key == "keep_arg_on_logs"){
                
                if(value_true) config::keep_arg_on_logs = true;

            } else if (key == "save_logs_to_file"){

                if(value_true) config::save_logs_to_file = true;  
                
            } else if (key == "custom_prompt"){

                if(value_true) config::custom_prompt = true;
                    
            } else if (key == "custom_prompt_string"){

                config::custom_prompt_string = value;

            } else if (key == "show_path"){

                std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                config::show_path = value;

            } else if (key == "user_name"){

                if(value_true) config::user_name = true;

            } else if (key == "bash_like_prompt"){

                if(value_true) config::bash_like_prompt = true;

            } else if (key == "debug_mode"){

                if(value_true) config::debug_mode = true;
                
            } else if (key == "show_mem"){

                if(value_true) config::show_mem = true;
                
            } else if (key == "unknown_os_allowed"){

                if(value_true) config::unknown_os_allowed = true;
                
            } else if (key == "win_always"){

                if(value_true) config::win_always = true;
                
            } else if (key == "linux_always"){
                if(value_true) config::linux_always = true;
                
            } else if (key == "linux_distro"){
                config::linux_distro = value;
            } else if (key == "distro_not_os"){

                if(value_true) config::distro_not_os = true;
                
            } else if (key == "full_name_OS"){
                if(value_true) config::full_name_OS = true;
                
            } else if (key == "apply_plugins"){
                if(value_true) config::apply_plugins = true;
                
            } else {
                Log::log(std::string("Unknown Configuration Key: " + key), true);
            }
        }
        
        Log::log("About to read from configuration", false);
            
        for(int i = 0; i < readconf::configs.size(); i++){
            Log::log(configs.at(i), false);
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

    /*
        "An idiot admires complexity, a genius admires simplicity, a physicist tries to make it
        simple, for an idiot anything the more complicated it is the more he will admire it, if
        you make something so clusterfucked he can't understand it he's gonna think you're a
        god cause you made it so complicated nobody can understand it. That's how they write
        journals in Academics, they try to make it so complicated people think you're a genius"

        RIP Terry Davis, creator of TempleOS
    */
}
