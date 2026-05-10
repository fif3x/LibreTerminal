#include <iostream>
#include <filesystem>
#include <cstdio>

namespace fs = std::filesystem;

int main(){
    while(true){
        std::cout << "LibreTerminal Plugin Manager\n-----------------------------" << std::endl;
        std::cout << "1. Remove Plugin" << std::endl;
        std::cout << "2. Add Plugin" << std::endl;
        std::cout << "3. Show Current Plugins" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter option: ";

        char option = ' ';
        std::cin >> option;

        if(option == '1'){
            std::cout << "Plugin name: ";
            std::string plugin;
            std::cin >> plugin;

            #ifdef _WIN32
                std::string path = (fs::path(std::getenv("APPDATA")) / "\\libreterminal\\plugins\\" / plugin).string();
            #else
                std::string path = (fs::path(std::getenv("HOME")) / ".config/libreterminal/plugins/" / plugin).string();
            #endif

            int status = remove(path.c_str());

            if (status != 0) {
                std::perror("Error deleting file");
            }
            else {
                std::cout << "Succesfully deleted file" << std::endl;
            }

        } else if (option == '2') {
            std::cout << "Plugin location: ";
            std::string location;
            std::cin >> location;

            std::cout << "Plugin name: ";
            std::string plugin;
            std::cin >> plugin;

            #ifdef _WIN32
                std::string path = (fs::path(std::getenv("APPDATA")) / "\\libreterminal\\plugins\\" / plugin).string();
            #else
                std::string path = (fs::path(std::getenv("HOME")) / ".config/libreterminal/plugins/" / plugin).string();
            #endif
            
            fs::copy_file(location, path);

        } else if (option == '3') {
            #ifdef _WIN32
                std::string path = (fs::path(std::getenv("APPDATA")) / "\\libreterminal\\plugins\\").string();
            #else
                std::string path = (fs::path(std::getenv("HOME")) / ".config/libreterminal/plugins/" ).string();
            #endif
            
            for (const auto & entry : fs::directory_iterator(path)){
                std::cout << entry.path() << std::endl;
            }

        } else if (option == '4') {
            exit(0);
        } else {
            std::cout << "Invalid Option" << std::endl;
        }

    }

    return 0;
}