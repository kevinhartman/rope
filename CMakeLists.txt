cmake_minimum_required(VERSION 2.6)

project(rope)

add_subdirectory(capstone)

add_definitions(-std=c++11)
add_executable(rope main.cpp)

target_link_libraries(rope capstone-shared)
