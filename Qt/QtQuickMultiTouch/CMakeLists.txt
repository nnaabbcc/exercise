
cmake_minimum_required(VERSION 3.15)
project(QtQuickMultiTouch)

find_package(VTK REQUIRED)
find_package(Qt5 5.15.2 COMPONENTS Gui Quick REQUIRED)

add_subdirectory(src)
