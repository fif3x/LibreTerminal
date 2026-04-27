#include <iostream>
#include "../../include/main/os.h"
#include "../../include/main/configvars.h"


void print_os()
{
    os OS = detect_os();
    
    if (OS == os::WIN)
<<<<<<< HEAD
    {   
        if(config::full_name_OS){
            std::cout << "Windows";
        }
        else std::cout << "WIN";
=======
    {    
        if(config::full_name_OS){
            std::cout << "Windows>";
        } else {
            std::cout << "WIN>";
        }
>>>>>>> 97451cc58be61cd474b30c9f359110f26ddd4230
    }
    else if (OS == os::LINUX)
    {
        if(config::full_name_OS){
<<<<<<< HEAD
            std::cout << "Linux";
        }
        else std::cout << "LNX";
=======
            std::cout << "Linux>";
        } else {
            std::cout << "LNX>";
        }
>>>>>>> 97451cc58be61cd474b30c9f359110f26ddd4230
    }
    else
    {
        std::cout << "UNK";
    }
}
