cmake_policy(SET CMP0075 NEW)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in ${LLVM_DIR}")

add_subdirectory(core)

add_executable(ferret compiler.cpp)
target_link_libraries(ferret PRIVATE core_)
