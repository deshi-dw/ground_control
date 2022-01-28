cmake_minimum_required(VERSION 3.11)

project(libstem_gamepad
  LANGUAGES CXX
)

message("configuring libstem_gamepad")

add_library(libstem_gamepad
    source/gamepad/Gamepad.h
    source/gamepad/Gamepad_private.h
    source/gamepad/Gamepad_private.c
    source/gamepad/Gamepad_linux.c
)

target_link_libraries(libstem_gamepad pthread)