add_custom_target(integration_tests ALL
    DEPENDS
        chimera_host
        chimera_sdk
        chimera_add
        chimera_sub
        chimera_mul
        chimera_div
)

set(INTEGRATION_BINARY_DIR ${PROJECT_BINARY_DIR}/integration)

add_custom_command(TARGET integration_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}/plugins
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}/plugins/add
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}/plugins/sub
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}/plugins/mul
    COMMAND ${CMAKE_COMMAND} -E make_directory ${INTEGRATION_BINARY_DIR}/plugins/div

    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_host> ${INTEGRATION_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_sdk> ${INTEGRATION_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_add> ${INTEGRATION_BINARY_DIR}/plugins/add
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE_DIR:chimera_add>/plugin.json" ${INTEGRATION_BINARY_DIR}/plugins/add
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_sub> ${INTEGRATION_BINARY_DIR}/plugins/sub
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE_DIR:chimera_sub>/plugin.json" ${INTEGRATION_BINARY_DIR}/plugins/sub
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_mul> ${INTEGRATION_BINARY_DIR}/plugins/mul
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE_DIR:chimera_mul>/plugin.json" ${INTEGRATION_BINARY_DIR}/plugins/mul
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:chimera_div> ${INTEGRATION_BINARY_DIR}/plugins/div
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE_DIR:chimera_div>/plugin.json" ${INTEGRATION_BINARY_DIR}/plugins/div
)