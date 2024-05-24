add_library(chimera_sub MODULE
    sub.cpp
)

target_link_libraries(chimera_sub PUBLIC chimera::sdk)

set_target_properties(chimera_sub PROPERTIES
    EXPORT_NAME sub
    OUTPUT_NAME sub
)

add_custom_command(TARGET chimera_sub POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/plugin.json ${CMAKE_CURRENT_BINARY_DIR}
)
