cmake_minimum_required(VERSION 3.14)
project(PanguTest)

set(CMAKE_CXX_STANDARD 11)
#include_directories(${PROJECT_SOURCE_DIR})
set(WORKSPACE ${PROJECT_SOURCE_DIR})

message(STATUS "1WORKSPACE IS ${WORKSPACE}")
add_library(vector_test vector_test.cpp)

add_executable(PanguTest main.cpp registerer.cpp multi_base.cpp multi_base.h size_of_empty_class.cpp size_of_empty_class.h)
target_link_libraries(PanguTest vector_test)

add_executable(vector_test_main vector_test_main.cpp)

add_subdirectory(list)
#add_executable(list list/list_test_main.cpp)

add_subdirectory(map)
add_subdirectory(vector)