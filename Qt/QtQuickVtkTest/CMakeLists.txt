
cmake_minimum_required(VERSION 3.15)
project(QtQuickVtkTest)

find_package(VTK COMPONENTS
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
REQUIRED
)
find_package(Qt5 5.15.2 COMPONENTS Gui Quick REQUIRED)

add_subdirectory(src)
