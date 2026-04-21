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
#include <cstdint>

#include <string.h>

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
        
        pl::load_plugin_symbol(plugins, "before_prompt", {});
        prompt();
        pl::load_plugin_symbol(plugins, "after_prompt", {});

        std::getline(std::cin, input); // capture full line, this helps so we can check if the line is empty

        pl::load_plugin_symbol(plugins, "input", input.c_str());

        
        auto it = input.find(' ');
        if (it != std::string::npos) {
            arg1 = input.substr(it);
            input = input.substr(0, it);           
        }
        
        if(DEBUG){
            dbg(input, "input");
            dbg(arg1, "arg1");
        }

        if (input == "quit" || input == "exit" || input == "Quit" || input == "Exit")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            break; // quit libre terminal
        } 
        else if (input == "exec" || input == "Exec" || input == "execute")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            if (!arg1.empty() && arg1.front() == '"' && arg1.back() == '"') {
                arg1 = arg1.substr(1, arg1.size() - 2);
            }

            std::system((arg1).c_str());
        }
        else if (input == "ping" || input == "Ping")
        {
            LOG;
            status_code = 0;
            error_code = 0;

            std::system(("ping" + arg1).c_str());
        }
        else if (input == "show_ip")
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
        else if (input == "help" || input == "Help")
        {
            std::cout << "LIST OF COMMANDS\n" <<
                "1. quit | exit - exits program\n" <<
                "2. help - shows list of commands\n" <<
                "3. clear - clears output/screen\n" <<
                "4. logs - shows logs\n" <<
                "5. show_os - Shows OS being used\n" <<
                "6. exec - executes the command given in the argument\n" <<
                "7. show_ip - shows ip\n" <<
                "8. ping - pings an ip given at [arg1]\n" <<
                "9. show_shell - show shell detected\n" <<
                "10. exec - executes command given at [arg1]\n" <<
                "11. show_conf - shows configuration\n" << 
                "12. echo - outputs what is given on [arg1]\n" <<
            std::endl;

            status_code = 0;
            error_code = 0;
            LOG;
            
            // get help
        }
        else if (input.empty() || (input.size() > 1 && input.at(1) == ' ') || input == "\n")
        { // so it doesnt look buggy
        
        }

        else if (input == "clear" || input == "cls" || input == "Clear" || input == "CLS" || input == "CLEAR")
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
        } else if (input == "show_shell" || input == "show_Shell"){
            LOG;
            error_code = 0;
            status_code = 0;

            std::cout << config::shell << std::endl;

        } else if (input == "show_conf" || input == "show_Conf" || input == "show_config" || input == "show_Config"){
            LOG;
            error_code = 0;
            status_code = 0;

            for(int index = 0; index < readconf::configs.size(); index++){
                std::cout << readconf::configs.at(index) << std::endl;
            }
        }
        else if (input == "logs" || input == "Logs" || input == "LOGS"){
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
        } else if (input == "echo" || input == "Echo"){
            LOG;
            error_code = 0;
            status_code = 0;

            system((input + arg1).c_str());
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
            Log::log(input, false);
        }    
    }

    // i use fedora btw

    return 0; // end program
}