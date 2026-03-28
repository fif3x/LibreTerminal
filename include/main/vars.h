#ifndef VARS_H
#define VARS_H

#include <string>
#include <cstdint>

extern std::string input;
extern std::string arg1;
extern bool minimum;
extern bool close_conf_before_reading;

extern uint8_t error_code;  // 0 means no error
extern uint8_t status_code; // 0 means success, 1 means fail

#endif