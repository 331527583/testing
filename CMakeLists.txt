cmake_minimum_required(VERSION 3.14)
project(PanguTest)

set(CMAKE_CXX_STANDARD 11)

add_library(vector_test vector_test.cpp)

add_executable(PanguTest main.cpp registerer.cpp multi_base.cpp multi_base.h size_of_empty_class.cpp size_of_empty_class.h)
target_link_libraries(PanguTest vector_test)
