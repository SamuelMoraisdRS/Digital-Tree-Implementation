cmake_minimum_required(VERSION 3.10)

# Project name
project(DigitalTreeProject)

set(CMAKE_CXX_STANDARD 11)

# src files
add_executable(DigitalTreeProject main.cpp digital_tree.cpp)

# dirs
target_include_directories(DigitalTreeProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
