#include "../../include/main/os.h"
#include "../../include/main/configvars.h"

#include <filesystem>
#include <iostream>

void prompt(){
    namespace fs = std::filesystem;

    if(config::custom_prompt){
        std::cout << config::custom_prompt_string;
    } else if (config::distro_not_os){
        std::cout << config::linux_distro;
        if(config::show_path) std::cout << "@" << fs::current_path();
        std::cout << "> ";
    } else if (config::user_name){
        
    } else {
        print_os();
        if(config::show_path) std::cout << "@" << fs::current_path();
        std::cout << "> ";
    }
}