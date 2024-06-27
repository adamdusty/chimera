add_custom_target(package ALL
    DEPENDS
        chimera_host
        chimera_sdk
        chimera_core
        chimera_rend
)

set(DIR ${PROJECT_BINARY_DIR}/package)

add_custom_command(TARGET package POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}/plugins
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}/plugins/chimera/rend/0.1.0
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}/plugins/chimera/core/0.1.0


    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_host> ${DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_sdk> ${DIR}

    # rend
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chimera::rend> ${DIR}/plugins/chimera/rend/0.1.0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:chimera::rend>/plugin.json" ${DIR}/plugins/chimera/rend/0.1.0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:wgpu> ${DIR}/plugins/chimera/rend/0.1.0

    # core
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chimera::core> ${DIR}/plugins/chimera/core/0.1.0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:chimera::core>/plugin.json" ${DIR}/plugins/chimera/core/0.1.0

    COMMAND_EXPAND_LISTS
)

if(WIN32)

add_custom_command(TARGET package POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_RUNTIME_DLLS:chimera_host>
        $<TARGET_RUNTIME_DLLS:chimera::sdk>
        ${DIR}
        COMMAND_EXPAND_LISTS
)

endif()