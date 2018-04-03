
include(CMakeToolsHelpers OPTIONAL)

cmake_minimum_required(VERSION 2.8)

project(HelloWorld)

add_subdirectory(lib)

add_executable(HelloWorld helloworld.cpp)

target_link_libraries(HelloWorld lib_hello)