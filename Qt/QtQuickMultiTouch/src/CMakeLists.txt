
set(module_name QtQuickMultiTouch)

add_executable(${module_name} WIN32
    main.cpp
    main.qrc
)

target_link_libraries(${module_name} PRIVATE
    ${VTK_LIBRARIES}
    Qt5::Quick
)

set_target_properties(${module_name} PROPERTIES
    DEBUG_POSTFIX _d
    AUTOMOC ON
    AUTORCC ON
)
