
cmake_minimum_required(VERSION 3.15)

project(QtQuickVtkTest)

# Use the standard c++17 for this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(VTK 9.3.1 COMPONENTS
    DICOM
    InteractionWidgets
    InteractionImage
    InteractionStyle
    RenderingOpenGL2
    IOImage
    CommonColor
    ImagingColor
    RenderingAnnotation
    ImagingStatistics
    ImagingMath
    GUISupportQtQuick
    RenderingVolumeOpenGL2
    IOXML
    REQUIRED
)

find_package(Qt5 5.15.2 COMPONENTS
    Gui
    Quick
    REQUIRED
)

add_subdirectory(src)

