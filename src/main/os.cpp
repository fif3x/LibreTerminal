#include <iostream>
#include "../../include/main/os.h"
#include "../../include/main/configvars.h"


void print_os()
{
    os OS = detect_os();
    
    if (OS == os::WIN)
    {    
        if(config::full_name_OS){
            std::cout << "Windows>";
        } else {
            std::cout << "WIN>";
        }
    }
    else if (OS == os::LINUX)
    {
        if(config::full_name_OS){
            std::cout << "Linux>";
        } else {
            std::cout << "LNX>";
        }
    }
    else
    {
        std::cout << "UNK>";
    }
}
