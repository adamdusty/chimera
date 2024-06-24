add_custom_target(package ALL
    DEPENDS
        chimera_host
        chimera_sdk
        chimera_rend
)

set(DIR ${PROJECT_BINARY_DIR}/package)

add_custom_command(TARGET package POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}/plugins
    COMMAND ${CMAKE_COMMAND} -E make_directory ${DIR}/plugins/chimera/rend/0.1.0


    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_host> ${DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_sdk> ${DIR}

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chimera::rend> ${DIR}/plugins/chimera/rend/0.1.0
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:chimera::rend>/plugin.json" ${DIR}/plugins/chimera/rend/0.1.0
)