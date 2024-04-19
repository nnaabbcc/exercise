cmake_minimum_required(VERSION 3.15)

project(QtPdfTest)

find_package(Qt5 COMPONENTS
    Pdf
    Widgets
    Core
    REQUIRED)

add_executable(QtPdfTest WIN32
    QtPdfTest.cpp
)

target_link_libraries(QtPdfTest PRIVATE
    Qt5::Pdf
    Qt5::Widgets
    Qt5::Core
)
