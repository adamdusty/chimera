add_library(chimera_mul MODULE
    mul.cpp
)

target_link_libraries(chimera_mul PUBLIC chimera::sdk)

set_target_properties(chimera_mul PROPERTIES
    EXPORT_NAME mul
    OUTPUT_NAME mul
)

add_custom_command(TARGET chimera_mul POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/plugin.json ${CMAKE_CURRENT_BINARY_DIR}
)
