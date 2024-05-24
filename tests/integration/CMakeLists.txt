cmake_minimum_required(VERSION 3.29)

project(
    chimera_integration_tests
)

add_subdirectory(plugins/add)
add_subdirectory(plugins/sub)
add_subdirectory(plugins/mul)
add_subdirectory(plugins/div)

file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/manifest.json
    DESTINATION ${INTEGRATION_BINARY_DIR}
)