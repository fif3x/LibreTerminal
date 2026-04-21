// Include your libraries here. For example `#include <iostream>`




// to compile, use "g++ -shared -fPIC -o your_plugin_name.so plugin_template.cpp"

#ifdef _WIN32 // detect it its windows
    #define PLUGIN_EXPORT extern "C" __declspec(dllexport) // plugin export for windows
#else // other operating systems
    #define PLUGIN_EXPORT extern "C"
#endif

PLUGIN_EXPORT void start(){
    // here what is done when the program starts
}

PLUGIN_EXPORT void before_prompt(){
    // here what is done before the prompt
}

PLUGIN_EXPORT void after_prompt(){
    // here what is done after the prompt
}

PLUGIN_EXPORT void input(const char* input){ // remember that `input` is a type of const char*, not std::string
    // here what is done with the input from the user
}