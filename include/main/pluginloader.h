#ifndef PLUGIN_LOADER_H
#define PLUGIN_LOADER_H

#include <vector>
#include <string>
#include <optional>

namespace pluginloader {
    std::vector <std::string> locate_plugins();
    void load_plugin_symbol(std::vector<std::string> plugins, std::string smybol, std::optional<const char*> var);
    
}

#endif  