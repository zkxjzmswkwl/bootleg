cmake_minimum_required(VERSION 3.22)
project(bootleg)
set(CMAKE_CXX_STANDARD 23)


add_library(bootleg src/value_map.cpp)

target_include_directories(bootleg PUBLIC src)
