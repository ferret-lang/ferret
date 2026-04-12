# Set the minimum version required for CMake
cmake_minimum_required(VERSION 3.11)

# Set the name of the project
project(ferret)

# Set C++ standard and other properties
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for source code and testing
add_subdirectory(src)
enable_testing()
add_subdirectory(test)