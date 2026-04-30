#include <iostream>
#include <cstdlib>

#include "../../include/main/os.h"
#include "../../include/main/configvars.h"

#ifdef __linux__
    #include <sys/types.h>
    #include <pwd.h>
    #include <unistd.h>
    #include <limits.h>
#elif defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <Lmcons.h>
#endif

void print_os()
{
    os OS = detect_os();
    
    if (OS == os::WIN)
    {   
        if(config::full_name_OS){
            std::cout << "Windows";
        }
        else std::cout << "WIN";
    }
    else if (OS == os::LINUX)
    {
        if(config::full_name_OS){
            std::cout << "Linux";
        }
        else std::cout << "LNX";
    }
    else
    {
        std::cout << "UNK";
    }
}

std::string get_username(){
    
    #if defined(_WIN32) || defined(_WIN64)

    char username[UNLEN + 1] = { };
    DWORD username_len = UNLEN + 1;

    if(GetUserNameA(username, &username_len)){
        return username;
    } else {
        std::cerr << "ERROR: " << GetLastError() << std::endl;
        return "USER";
    }   

    #elif defined(__linux__)

    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);

    if(pw){
        return pw->pw_name;
    } else {
        return "USER";
    }

    #else
    return "UNK_USER";
    #endif
}

std::string get_hostname(){
    #if defined(_WIN32) || defined(_WIN64)
    char info_buf[256] = {  };
    DWORD buf_char_count = sizeof(info_buf);

    if(!GetComputerNameA(info_buf, &buf_char_count)){
        printError("GetComputerName"); 
        return "HOSTNAME";
    }

    return std::string(info_buf);

    #elif defined(__linux__)
    char hostname[HOST_NAME_MAX];
    
    if(gethostname(hostname, HOST_NAME_MAX) != 0){
        return "HOSTNAME";
    }

    return std::string(hostname);
    #else
    return "HOSTNAME";
    #endif

}