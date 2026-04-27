#include "../../include/main/vars.h"
#include <string>
#include <cstdint>

std::string raw_input = { };
std::string input = { };
std::string arg1 = { };
bool minimum = false;
bool close_conf_before_reading = true;

uint8_t error_code = 0;  // 0 means no error
uint8_t status_code = 0; // 0 means success, 1 means fail