set(module_name add_block)

add_executable(${module_name}
    add_block.cu
)

set_target_properties(${module_name} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
