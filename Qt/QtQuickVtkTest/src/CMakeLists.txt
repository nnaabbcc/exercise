
set(module_name QtQuickVtkTest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${module_name} WIN32
    main.cpp
    main.qrc
)

target_link_libraries(${module_name} PRIVATE
    ${VTK_LIBRARIES}
    Qt5::Quick
)

set_target_properties(${module_name} PROPERTIES DEBUG_POSTFIX _d)

vtk_module_autoinit(TARGETS ${module_name} MODULES VTK::RenderingVolumeOpenGL2)