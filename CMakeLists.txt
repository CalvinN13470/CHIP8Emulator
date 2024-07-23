cmake_minimum_required(VERSION 3.28)

set(This CHIP8Emulator)

project(${This} C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    src/chip8context.hpp
    src/chip8display.hpp
    src/chip8font.hpp
    src/chip8keypad.hpp
    src/chip8timer.hpp
    src/constants.hpp
    src/interpreter.hpp
    src/structures.hpp
    src/exceptions/null_display_exception.hpp
)

set(Sources
    src/chip8context.cpp
    src/chip8display.cpp
    src/chip8keypad.cpp
    src/chip8timer.cpp
    src/interpreter.cpp
    src/exceptions/null_display_exception.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(chip8tests)