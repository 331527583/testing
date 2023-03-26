#project(vector LANGUAGES CXX)
project(vector CXX)

cmake_minimum_required(VERSION 3.10)
message(STATUS "vector project WORKSPACE IS ${WORKSPACE}")
add_executable(vector_test_main2 vector_test_main.cpp)
target_include_directories(vector_test_main2 PUBLIC ${WORKSPACE})