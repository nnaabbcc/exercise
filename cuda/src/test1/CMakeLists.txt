set(module_name test1)

add_executable(${module_name}
    test1.cu
)

set_target_properties(${module_name} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    CUDA_ARCHITECTURES all
)
