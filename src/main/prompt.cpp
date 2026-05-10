#include "../../include/main/os.h"
#include "../../include/main/configvars.h"

#include <filesystem>
#include <iostream>
#include <algorithm>

void show_path();

void prompt(){
    namespace fs = std::filesystem;

    if(config::custom_prompt){
        std::cout << config::custom_prompt_string;
    } else if (config::distro_not_os){
        std::cout << config::linux_distro;
        std::cout << "@";
        show_path();

        std::cout << "> ";
    } else if (config::user_name){
        std::cout << get_username();
        std::cout << "@";
        show_path();

        std::cout << "> ";
    } else if (config::bash_like_prompt){
        std::cout << get_username() << "@" << get_hostname() << ":";
        show_path();

        std::cout << "> ";

    } else {
        print_os();
        std::cout << "@";
        show_path();

        std::cout << "> ";
    }
}

void show_path(){
    namespace fs = std::filesystem;

    if(config::show_path == "full"){
        std::cout << fs::current_path();
    } else if (config::show_path == "dir"){

        fs::path path = fs::current_path();
        path = path.filename();

        std::string path_str = path.string();

        if (!path_str.empty() && path_str.front() == '"') path_str.erase(0, 1);
        if (!path_str.empty() && path_str.back() == '"') path_str.pop_back();

        std::cout << path_str;
    }
}