file(GLOB_RECURSE headers "*.h" "*.hpp")
file(GLOB_RECURSE sources "*.cpp")

add_library(core_ SHARED ${headers} ${sources})
target_include_directories(core_ PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
