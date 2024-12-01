cmake_minimum_required(VERSION 3.10)
project(pointlibrary)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_definitions(-std=c++17 -Ofast -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers)
add_compile_options(-Wall -Wextra -Werror=unused-variable)

include_directories( include )

add_library(MultiCloud STATIC src/types.cpp src/io.cpp)
target_include_directories(MultiCloud PUBLIC include)

add_library(MultiCloudVisualizer STATIC src/point_visualizer.cpp)
target_include_directories(MultiCloudVisualizer PUBLIC include)
target_link_libraries(MultiCloudVisualizer X11 GL GLU m)
target_compile_definitions(MultiCloudVisualizer PRIVATE GL_GLEXT_PROTOTYPES)

###     GTEST     ###
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(types_test test/point_types_test.cpp)
target_link_libraries(types_test MultiCloud ${GTEST_LIBRARIES} pthread)
add_test(
  NAME types_test
  COMMAND types_test
)

add_executable(point_visualizer_test test/visualizer/point_visualizer_test.cpp)
target_link_libraries(point_visualizer_test MultiCloudVisualizer ${GTEST_LIBRARIES} pthread)
