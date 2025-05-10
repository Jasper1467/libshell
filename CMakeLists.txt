cmake_minimum_required(VERSION 3.10)

project(libshell_proj)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test src/main.cpp include/libshell.hpp)
