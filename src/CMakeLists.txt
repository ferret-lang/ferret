add_subdirectory(console)

add_executable(ferret
  compiler.cpp
)

target_link_libraries(ferret PRIVATE console)