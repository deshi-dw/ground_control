cmake_minimum_required(VERSION 3.11)

project(serialib
  LANGUAGES CXX
)

message("configuring serialib")

add_library(serialib
    serialib.h
    serialib.cpp
)