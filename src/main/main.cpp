/*
PROGRAM LICENSE:



Libre Terminal

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.



*/

/*

NOTE: If you experience any errros, please contact the developers on the following platforms:

@fifex._ on Instagram
t.me/fif3x for Telegram

E-MAIL: fif3x@disroot.org     NOTE: might not respond quickly, also this e-mail might change

*/

#include <iostream>
#include <filesystem>
#include <algorithm>

#if defined(__linux__)
#include <unistd.h>
#endif

#include "../../include/main/log.h"
#include "../../include/main/os.h"
#include "../../include/main/readconf.h"
#include "../../include/main/vars.h"
#include "../../include/main/configvars.h"
#include "../../include/main/pluginloader.h"
#include "../../include/main/debug.hpp"
#include "../../include/main/prompt.h"

#define LOG log = true
#define DEBUG config::debug_mode

int main()
{
    namespace pl = pluginloader;
    namespace fs = std::filesystem;

    readconf::read_config(); // from readconf.h

    std::vector<std::string> plugins = { };

    os OS;
    OS = detect_os();


    if(config::linux_always){
        OS = lnx;
    } else if (config::win_always){
        OS = win;
    }

    if(DEBUG){
        dbg(OS, "OS");
    }

    if(!config::unknown_os_allowed){
        if(OS == unk){
            std::cout << "ERROR: Unknown OS found and config rule `unknown_os_allowed` is false. Please change and rerun the program." << std::endl;
            exit(1);
        }
    }


    if(config::apply_plugins){
        plugins = pl::locate_plugins();

        pl::load_plugin_symbol(plugins, "start", {});

    }

    while (true)
    {
        bool log = false;

        arg1 = { }; // std::string

        pl::load_plugin_symbol(plugins, "before_prompt", {}); // no need to recheck if config::apply_plugins is true, because if its not, 'plugins' will remain empty, therefore, no plugins to cycle through.
        prompt();
        pl::load_plugin_symbol(plugins, "after_prompt", {});

        std::getline(std::cin, raw_input); // capture full line, this helps so we can check if the line is empty

        pl::load_plugin_symbol(plugins, "raw_input", raw_input.c_str());

        if(DEBUG){
            dbg(raw_input, "raw_input");
        }

        raw_input.erase(0, raw_input.find_first_not_of(" \t")); // start
        raw_input.erase(raw_input.find_last_not_of(" \t") + 1); // end

        auto it = raw_input.find(' ');
        if (it != std::string::npos) {
            input = raw_input.substr(0, it);
            if(input == "cd"){
                arg1 = raw_input.substr(it + 1);
            } else {
                arg1 = raw_input.substr(it);
            }
        } else {
            input = raw_input;
        }

        pl::load_plugin_symbol(plugins, "input", input.c_str());

        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        if(DEBUG){
            dbg(input, "input");
            dbg(arg1, "arg1");
        }

        if (input == "quit" || input == "exit")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            break; // quit libre terminal
        }
        else if (input == "exec" || input == "execute")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            if (!arg1.empty() && arg1.front() == '"' && arg1.back() == '"') {
                arg1 = arg1.substr(1, arg1.size() - 2);
            }

            std::system((arg1).c_str());
        }
        else if (input == "cd"){
            LOG;
            status_code = 0;
            error_code = 0;

            if(arg1.empty()){

                std::string home = { };

                if(OS == lnx){

                    const char* env = std::getenv("HOME");
                    if(env){
                        home = env;
                    }

                } else if(OS == win){

                    const char* env = std::getenv("USERPROFILE");
                    if(env){
                        home = env;
                    }

                    if(home.empty()){
                        const char* drive = std::getenv("HOMEDRIVE");
                        const char* path = std::getenv("HOMEPATH");

                        if(drive && path){
                            home = std::string(drive) + path;
                        }
                    }

                }

                std::error_code ec;
                if(!home.empty()){
                    fs::current_path(home, ec);
                }

                if(ec){
                    std::cout << "cd error: " << ec.message() << std::endl;

                    status_code = 1;
                    error_code = 1;
                }


            } else {
                if(fs::is_directory(arg1)){
                    fs::current_path(arg1);
                } else {
                    status_code = 1;
                    error_code = 6;

                    std::cout << "Directory does not exist" << std::endl;
                }
            }


        }
        else if (input == "pwd" || input == "show_directory" || input == "show_dir"){
            LOG;
            status_code = 0;
            error_code = 0;



            std::cout << fs::current_path() << std::endl;

        }
        else if (input == "ping")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            std::system(("ping" + arg1).c_str());
        }
        else if (input == "show_ip" || input == "showip")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            if(OS == lnx){
                std::system("ifconfig");
            } else if (OS == win){
                std::system("ipconfig");
            }
        }
        else if (input == "help")
        {
            std::cout << "LIST OF COMMANDS (NOTE; COMMANDS ARE NOT CASE SENSITIVE)\n" <<
                "1. quit/exit - exits program\n" <<
                "2. exec/execute [arg1] - executes command given on arg1\n" <<
                "3. cd [arg1] - changes directory to folder given on arg1\n" <<
                "4. pwd/show_directory/show_dir - shows directory currently in\n" <<
                "5. ping [arg1] - pings IP given on arg1\n" <<
                "6. show_ip/showip - shows ip and general IP configurations\n" <<
                "7. help - displays this message\n" <<
                "8. clear - clears screen\n" <<
                "9. show_shell/showshell - shows shell detected\n" <<
                "10. show_conf/showconf - shows configuration\n" <<
                "11. logs - Displays all messages logged\n" <<
                "12. show_os/showos - Shows OS detected\n" <<
                "13. echo [arg1] - outputs what is given on arg1\n" <<
                "14. pkg [arg1] - does operation, with argument and name that is given on arg1\n" <<
                "15. pr - executs previous command\n" <<
                "16. dir/show_dir/show_directory - shows files in the directory currently in\n" <<
                "17. shell [arg1] - calls the shell configured with the argument given on arg1\n" <<
            std::endl;

            status_code = 0;
            error_code = 0;
            LOG;

            // get help
        }
        else if (input.empty() || (input.size() > 1 && input.at(1) == ' ') || input == "\n")
        { // so it doesnt look buggy

        }

        else if (input == "clear" || input == "cls")
        {
            LOG;
            // clear screen
            if (OS == win)
            {
                error_code = 0;
                status_code = 0;
                std::system("cls"); // clearing terminal screen in windows
            }
            else if (OS == lnx) // from os.h
            {
                error_code = 0;
                status_code = 0;
                std::system("clear"); // clearing terminal screen in linux
            }
            else
            {
                error_code = 0;
                status_code = 0;

                if(config::unknown_os_allowed == true){
                    if(config::shell == "bash" || config::shell == "sh" || config::shell == "zsh" || config::shell == "fish"){
                        std::system("clear");
                    } else if (config::shell == "batch"){
                        std::system("cls");
                    }
                } else {

                }
            }
        } else if (input == "show_shell" || input == "showshell"){
            LOG;
            error_code = 0;
            status_code = 0;

            std::cout << config::shell << std::endl;

        } else if (input == "show_conf" || input == "show_config"){
            LOG;
            error_code = 0;
            status_code = 0;

            for(int index = 0; index < readconf::configs.size(); index++){
                std::cout << readconf::configs.at(index) << std::endl;
            }
        }
        else if (input == "logs"){
            LOG;
            error_code = 0;
            status_code = 0;

            for(int index = 0; index < Log::logs.size(); index++){
                std::cout << Log::logs.at(index) << "\n";
            }

        }
        else if (input == "show_os" || input == "showos"){
            LOG;
            error_code = true;
            status_code = true;

            std::string os = { };

            if(OS == lnx){
                os = "Linux";
            } else if (OS == win){
                os = "Windows";
            } else if (OS == unk){
                os = "Unknown";
            }

            std::cout << "Detected: " << os << " | Code: " << OS << std::endl;
        } else if (input == "echo"){
            LOG;
            error_code = 0;
            status_code = 0;

            system((input + arg1).c_str());
        }
        else if (input == "pkg"){
            LOG;
            error_code = 0;
            status_code = 0;

            if(!(OS == lnx)){
                error_code = 1;
                status_code = 7;
                std::cout << "Cannot use command pkg: Requires using Linux + being on the available distro list" << std::endl;
            } else {
                std::transform(config::linux_distro.begin(), config::linux_distro.end(), config::linux_distro.begin(), ::tolower);


                #define distro config::linux_distro

                if(distro == "debian" || distro == "ubuntu" || distro == "mint" || distro == "popos"){
                    std::system((std::string("apt") + " " + arg1).c_str());
                } else if (distro == "fedora" || distro == "centos" || distro == "rocky"){
                    std::system((std::string("dnf") + " " + arg1).c_str());
                } else {
                    error_code = 1;
                    status_code = 7;

                    std::cout << "Distro not available on the list; If its Arch, you need to parse it using 'exec', if its not, put a distro that uses the same package manager (e.g. fedora for dnf)" << std::endl;
                }

                #undef distro
            }

        } else if (input == "pr"){
            system(Log::logs.back().c_str());
        } else if (input == "dir" || input == "show_directory" || input == "showdirectory"){
            system(std::string(input + " " + arg1).c_str());
        } else if (input == "shell"){
            system((std::string(config::shell) + arg1).c_str());
        }
        else
        {
            if(config::auto_exec){
                system((input + arg1).c_str());
            }
            else{
                error_code = 2;
                status_code = 1;
                std::cerr << "ERROR 002" << std::endl;
            }

        }

        if (log){
            if(config::keep_arg_on_logs){
                Log::log(input + arg1, false);
            } else {
                Log::log(input, false);
            }
        }
    }

    // i use fedora btw

    return 0; // end program
}
