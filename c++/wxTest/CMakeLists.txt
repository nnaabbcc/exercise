cmake_minimum_required(VERSION 3.0)

project(wxTest)

set(srcs
    main.cpp
)

if(WIN32)
    # wxWidgets Finder
    set(wxWidgets_ROOT_DIR $ENV{WXWIN})
    set(wxWidgets_LIB_DIR ${wxWidgets_ROOT_DIR}/lib/vc_x64_lib)
    link_directories(${wxWidgets_LIB_DIR})

    set(wxWidgets_CONFIGURATION mswu)
    find_package(wxWidgets REQUIRED COMPONENTS core adv)
    set(wxWidgets_RELEASE_LIBRARIES ${wxWidgets_LIBRARIES})

    set(wxWidgets_CONFIGURATION mswud)
    find_package(wxWidgets REQUIRED COMPONENTS core adv)
    set(wxWidgets_DEBUG_LIBRARIES ${wxWidgets_LIBRARIES})

    add_executable(wxTest WIN32 ${srcs})
    target_compile_definitions(wxTest PRIVATE
        __WXMSW__
        UNICODE
        _UNICODE
    )
    target_include_directories(wxTest PRIVATE
        ${wxWidgets_ROOT_DIR}/include/msvc
        ${wxWidgets_ROOT_DIR}/include
    )
    target_link_libraries(wxTest PRIVATE debug ${wxWidgets_DEBUG_LIBRARIES})
    target_link_libraries(wxTest PRIVATE optimized ${wxWidgets_RELEASE_LIBRARIES})

endif()

if(UNIX)
    add_executable(wxTest ${srcs})
    find_package(wxWidgets REQUIRED COMPONENTS core adv)
    target_link_libraries(wxTest PRIVATE ${wxWidgets_LIBRARIES})
endif()
