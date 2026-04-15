add_subdirectory(core)

add_executable(ferret
  compiler.cpp
)

target_link_libraries(ferret PRIVATE core_)
