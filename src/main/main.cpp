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

#include "../../include/main/log.h"
#include "../../include/main/os.h"
#include "../../include/main/readconf.h"
#include "../../include/main/vars.h"

int main()
{
    
    
    readconf::read_config(); // from readconf.h

    os OS;
    OS = detect_os();
    
    if(OS == lnx){
        
    }
    
    while (true)
    {
        bool log = false;
        
        print_os(); // from os.h

        std::getline(std::cin, input); // capture full line, this helps so we can check if the line is empty.

        if (input == ":q" || input == "quit" || input == "exit")
        {
            status_code = 0;
            error_code = 0;
            break; // quit libre terminal
        }
        else if (input == "help" || input == "Help")
        {
            status_code = 0;
            error_code = 0;
            log = true;
            
            // get help
        }
        else if (input.empty() || input == " " || input == "\n")
        { // so it doesnt look buggy
        
        }

        else if (input == "clear" || input == "cls" || input == "Clear" || input == "CLS" || input == "CLEAR")
        { 
            log = true;
            // clear screen
            if (OS == win)
            {
                error_code = 0;
                status_code = 0;
                system("cls"); // clearing terminal screen in windows
            }
            else if (OS == lnx) // from os.h
            {
                error_code = 0;
                status_code = 0;
                system("clear"); // clearing terminal screen in linux
            }
            else
            {
            }
        }
        else if (input == "logs" || input == "Logs" || input == "LOGS"){
            log = true;
            error_code = 0;
            status_code = 0;
            for(int index = 0; index < Log::logs.size(); index++){
                std::cout << Log::logs.at(index) << "\n";
            }
        }
        else if (input == "show_os" || input == "showos"){
            log = true;
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
        }
        else
        {
            error_code = 2;
            status_code = 1;
            std::cout << "ERROR 002" << std::endl;
        }
        
        if (log){
            Log::log(input, false);
        }    
    }

    // i use fedora btw

    return 0; // end program
}