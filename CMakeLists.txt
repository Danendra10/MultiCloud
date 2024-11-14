cmake_minimum_required(VERSION 3.10)
project(pointlibrary)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-std=c++17 -Ofast -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers)
add_compile_options(-Wall -Wextra -Werror=unused-variable)

include_directories( include )

add_library(MultiCloud STATIC src/types.cpp src/io.cpp)
target_include_directories(MultiCloud PUBLIC include)
# add_library(io src/io.cpp)
# target_link_libraries(io X11 GL m)
# target_compile_definitions(io PRIVATE GL_GLEXT_PROTOTYPES)
