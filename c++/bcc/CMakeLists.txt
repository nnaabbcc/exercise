
cmake_minimum_required(VERSION 3.0)

project(BCC)

# Use the standard c++17 for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bcc
    bcc.cpp
)

add_executable(bcc_1
    bcc_1.cpp
)
