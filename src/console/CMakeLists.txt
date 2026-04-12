file(GLOB_RECURSE headers "*.h" "*.hpp")
file(GLOB_RECURSE sources "*.cpp")

add_library(console SHARED ${headers} ${sources})
target_include_directories(console PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)