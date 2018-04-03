
include(CMakeToolsHelper OPTIONAL)

cmake_minimum_required(VERSION 2.8)

aux_source_directory(. DIR_LIB_HELLO_SRCS)

add_library(lib_hello ${DIR_LIB_HELLO_SRCS})
