cmake_minimum_required(VERSION 4.0)
project(ferret)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ferret
        main.cpp
        base/Lexer.cpp
        base/Parser.cpp)
