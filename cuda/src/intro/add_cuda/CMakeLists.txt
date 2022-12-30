set(module_name add_cuda)

add_executable(${module_name}
    add_cuda.cu
)

set_target_properties(${module_name} PROPERTIES
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    CUDA_ARCHITECTURES all
)
