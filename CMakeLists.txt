cmake_minimum_required(VERSION 3.10)

project(staticPlanning2D)

set(INCLUDE_DIR /home/vr-laptop-30/Documents/code/cpp/staticPlanning2D/include)
set(SRC_DIR /home/vr-laptop-30/Documents/code/cpp/staticPlanning2D/src)
add_subdirectory(${SRC_DIR})

# Generate path
add_executable(generate_path test/generate_path.cpp)
target_include_directories(generate_path PUBLIC ${INCLUDE_DIR})
target_link_libraries(generate_path PRIVATE node2d supportLib pbPlots)