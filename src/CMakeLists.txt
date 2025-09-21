
# Create the main compiler executable
add_executable(compiler main.c)

# Include directories for the compiler
target_include_directories(compiler PRIVATE ${PROJECT_SOURCE_DIR}/include)
