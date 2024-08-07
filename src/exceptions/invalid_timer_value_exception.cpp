#include "invalid_timer_value_exception.hpp"

std::string InvalidTimerValueException::msg(){
    return "Current timer value invalid (valid values: 0-255)";
}