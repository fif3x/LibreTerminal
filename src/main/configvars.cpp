#include <string>
#include "../../include/main/configvars.h"

// --- general configs ---
std::string config::shell = { };
bool config::auto_exec = false;


// --- prompt configs ---
bool config::custom_prompt = false;
std::string config::custom_prompt_string = { };
std::string config::show_path = { "false" };
bool config::user_name = false;
bool config::bash_like_prompt = false;

bool config::debug_mode = false;
bool config::show_mem = false;

// --- OS configs ---
bool config::unknown_os_allowed = false;
bool config::win_always = false;
bool config::linux_always = false;
bool config::distro_not_os = false;

std::string config::linux_distro = { };

// --- Printing-related configs ---
bool config::full_name_OS = false;

// --- plugins configs ---
bool config::apply_plugins = false;

// --- custom configs --- (for custom builds of the program - make sure to sync include/main/configvars.h)