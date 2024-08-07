cmake_minimum_required(VERSION 3.28)

set(This chip8tests)

set(Sources
    timer_test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    CHIP8Emulator
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
