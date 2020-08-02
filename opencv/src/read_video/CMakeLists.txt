
set(module_name ReadVideo)

add_executable(${module_name}
    read_video.cpp
)

target_link_libraries(${module_name}
    PRIVATE ${OpenCV_LIBS}
)
