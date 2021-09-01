cmake_minimum_required(VERSION 3.15)

project(DeviceTree)

# Use the standard c++17 for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (ENABLE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "_d")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)

# This fixes issues on machines with default codepages that are not ASCII compatible, such as some CJK encodings
if (MSVC)
    add_compile_options("/utf-8")
endif()

add_executable(DeviceTree
    device_tree.cxx
)
set_target_properties(DeviceTree PROPERTIES DEBUG_POSTFIX _d)
