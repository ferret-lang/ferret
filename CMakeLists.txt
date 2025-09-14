cmake_minimum_required(VERSION 4.0)
project(ferret)

set(CMAKE_CXX_STANDARD 14)

add_executable(ferret
        main.cpp
        base/Lexer.cpp)
