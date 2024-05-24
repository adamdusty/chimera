add_library(chimera_div MODULE
    div.cpp
)

target_link_libraries(chimera_div PUBLIC chimera::sdk)

set_target_properties(chimera_div PROPERTIES
    EXPORT_NAME div
    OUTPUT_NAME div
)

add_custom_command(TARGET chimera_div POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/plugin.json ${CMAKE_CURRENT_BINARY_DIR}
)
