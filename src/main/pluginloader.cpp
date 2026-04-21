#include "../../include/main/pluginloader.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <optional>

#ifdef __linux__

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#define HANDLE_TYPE void*
#define HANDLE_FUNC dlopen(plugins.at(index).c_str(), RTLD_LAZY)
#define SYMBOL_FUNC dlsym(handle, symbol.c_str())
#define CLOSE_FUNC dlclose(handle)
#define ERROR_MSG dlerror()
#define FILE_EXTENSION ".so"

#define LIN

#elif defined(_WIN32)

#include <windef.h>
#include <libloaderapi.h>

#define HANDLE_TYPE HMODULE
#define HANDLE_FUNC LoadLibraryA(plugins.at(index).c_str())
#define SYMBOL_FUNC GetProcAddress(handle, symbol.c_str())
#define CLOSE_FUNC FreeLibrary(handle);
#define ERROR_MSG "Error when loading symbol"
#define FILE_EXTENSION ".dll"

#define WIN

#endif


namespace fs = std::filesystem;
namespace pl = pluginloader;

std::vector<std::string> pl::locate_plugins(){
    
    #ifdef _WIN32
        std::string path = (fs::path(std::getenv("APPDATA")) / "\\libreterminal\\plugins\\").string();
    #else
        std::string path = (fs::path(std::getenv("HOME")) / ".config/libreterminal/plugins/").string();
    #endif

    std::vector<std::string> files = { };

    for (const auto & entry : fs::directory_iterator(path)){
        std::cout << "Found file: " << entry.path() << std::endl;
        
        if(fs::is_regular_file(fs::status(entry.path().string()))){
            files.push_back(entry.path().string());
        }
        
    }

    std::cout << std::endl;


    for(int index = 0; index < files.size();){
        if (files.at(index).find(FILE_EXTENSION) != std::string::npos) {
            index++;
        } else {
            files.erase(files.begin() + index);
        }
    }
    

    return files;
}

void pl::load_plugin_symbol(std::vector<std::string> plugins, std::string symbol, std::optional<const char*> var){ // symbol is for dlsym()

    for(int index = 0; index < plugins.size(); index++){

        HANDLE_TYPE handle;
        handle = HANDLE_FUNC;
        char* error;

        
        if(symbol == "start"){

            void (*start)();

            if(!handle){
                fputs(ERROR_MSG, stderr);
                exit(1);
            }

            // start = dlsym(handle, symbol.c_str()); --- IGNORE ---
            start = reinterpret_cast<void (*)()>(SYMBOL_FUNC);

            if((error = ERROR_MSG) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            start();

            if(!start){
                std::cerr << "ERROR: Symbol" << symbol << " does not exist in " << plugins.at(index);
                return;
            }

            CLOSE_FUNC;


        } else if (symbol == "before_prompt"){
            void (*before_prompt)();

            if(!handle){
                fputs(ERROR_MSG, stderr);
                exit(1);
            }

            before_prompt = reinterpret_cast<void (*)()>(SYMBOL_FUNC);

            if((error = ERROR_MSG) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            before_prompt();

            if(!before_prompt){
                std::cerr << "ERROR: Symbol" << symbol << " does not exist in " << plugins.at(index);
                return;
            }

            CLOSE_FUNC;

        } else if (symbol == "after_prompt"){
            void (*after_prompt)();

            if(!handle){
                fputs(ERROR_MSG, stderr);
                exit(1);
            }

            after_prompt = reinterpret_cast<void (*)()>(SYMBOL_FUNC);

            if((error = ERROR_MSG) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            after_prompt();

            if(!after_prompt){
                std::cerr << "ERROR: Symbol" << symbol << " does not exist in " << plugins.at(index);
                return;
            }

            CLOSE_FUNC;

        }  else if (symbol == "input") {
            void (*input)(const char*);

            if(!handle){
                fputs(ERROR_MSG, stderr);
                exit(1);
            }

            input = reinterpret_cast<void (*)(const char*)>(SYMBOL_FUNC);

            if((error = ERROR_MSG) != NULL){
                fputs(error, stderr);
                exit(1);
            }

            input(var.value_or("N/A"));

            if(!input){
                std::cerr << "ERROR: Symbol" << symbol << " does not exist in " << plugins.at(index);
                return;
            }

            CLOSE_FUNC;

        } else {
            std::cout << "UNKNOWN SYMBOL: " << symbol << std::endl;
        }
    }
}