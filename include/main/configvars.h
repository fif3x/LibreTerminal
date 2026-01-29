#include <string>

namespace config{
    // --- general configs ---
    extern std::string shell;
    
    extern bool debug_mode;
    extern bool show_mem; // show the memory used
    
    // --- OS configs ---
    extern bool unknown_os_allowed;
    extern bool win_always;
    extern bool linux_always;
    extern bool distro_not_os; // false: os will be printed, true: distro will be printed. 
    
    extern std::string linux_distro; // leave it empty or put NULL if you dont use Linux
    
    // --- Printing-related configs ---
    extern bool full_name_OS;
    
    // --- plugins configs ---
    extern bool apply_plugins;
    
    // --- custom configs --- (this if for custom builds of the program)
}