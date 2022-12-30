set(module_name add)

add_executable(${module_name}
    add.cpp
)

set_target_properties(${module_name} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
