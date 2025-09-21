
# Find CMocka include and library paths
find_path(CMOCKA_INCLUDE_DIR cmocka.h
    PATHS /opt/homebrew/include
)

find_library(CMOCKA_LIBRARY NAMES cmocka
    PATHS /opt/homebrew/lib
)

# Ensure that CMocka is found
if (NOT CMOCKA_INCLUDE_DIR OR NOT CMOCKA_LIBRARY)
    message(FATAL_ERROR "CMocka library or header not found")
endif()

# Include the CMocka directory
include_directories(${CMOCKA_INCLUDE_DIR})

# Collect all the test source files
file(GLOB TEST_SOURCES "*.c")

# Create the test executable
add_executable(run_tests ${TEST_SOURCES})

# Link the test executable with the CMocka library
target_link_libraries(run_tests PRIVATE ${CMOCKA_LIBRARY})

# Register the test executable with CTest
add_test(NAME CompilerTests COMMAND run_tests)

