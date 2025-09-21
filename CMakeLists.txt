cmake_minimum_required(VERSION 3.10)
project(FerretCompiler)

# Setting the C standard for the project.
set(CMAKE_C_STANDARD 23)

# Adding include directories for headers.
include_directories(include)

# Add testing support.
enable_testing()

# Adding the source files to the project.
add_subdirectory(src)
add_subdirectory(tests)
