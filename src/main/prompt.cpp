#include "../../include/main/os.h"
#include "../../include/main/configvars.h"

#include <iostream>

void prompt(){
    if(config::custom_prompt){
        std::cout << config::custom_prompt_string;
    } else if (config::distro_not_os){
        std::cout << config::linux_distro << "> ";
    } else {
        print_os();
    }
}