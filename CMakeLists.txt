cmake_minimum_required(VERSION 3.10.2)

project(staticPlanning2D)

set(INCLUDE_DIR /home/vr-laptop-30/Documents/code/cpp/staticPlanning2D/include)
set(SRC_DIR /home/vr-laptop-30/Documents/code/cpp/staticPlanning2D/src)


add_subdirectory(${SRC_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals)

find_package(NLopt REQUIRED)
include_directories(${NLOPT_INCLUDE_DIRS})

# Generate path
add_executable(generate_path test/generate_path.cpp)
target_include_directories(generate_path PUBLIC ${INCLUDE_DIR})
target_link_libraries(generate_path PRIVATE node2d supportLib pbPlots grid_2d_solver)

# Generate path weighted
add_executable(generate_path_weighted test/generate_path_weighted.cpp)
target_include_directories(generate_path_weighted PUBLIC ${INCLUDE_DIR})
target_link_libraries(generate_path_weighted PRIVATE node2d supportLib pbPlots grid_2d_solver)

# NLopt test
add_executable(nlopt_practice test/nlopt_practice.cpp)
target_include_directories(nlopt_practice PUBLIC ${INCLUDE_DIR})
target_link_libraries(nlopt_practice PRIVATE ${NLOPT_LIBRARIES})