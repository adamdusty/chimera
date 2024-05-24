add_library(chimera_add MODULE
    add.cpp
)

target_link_libraries(chimera_add PUBLIC chimera::sdk)

set_target_properties(chimera_add PROPERTIES
    EXPORT_NAME add
    OUTPUT_NAME add
)

add_custom_command(TARGET chimera_add POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/plugin.json ${CMAKE_CURRENT_BINARY_DIR}
)
