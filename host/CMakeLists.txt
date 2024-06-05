cmake_minimum_required(VERSION 3.29)

project(
    chimera_host
    LANGUAGES CXX
)

include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

add_library(host_lib OBJECT)

target_link_libraries(host_lib PUBLIC chimera::sdk nlohmann_json::nlohmann_json)

target_sources(host_lib PRIVATE
    src/pack.cpp
    src/plugin.cpp
    "$<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/src/library/windows.cpp>"
    "$<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/library/linux.cpp>"
    "$<$<PLATFORM_ID:Windows>:${CMAKE_CURRENT_SOURCE_DIR}/src/utils/windows.cpp>"
    "$<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/src/utils/linux.cpp>"
)


target_include_directories(
    host_lib
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

add_executable(chimera_host)


# Add compile options
add_dev_compile_opts(chimera_host)

target_sources(chimera_host PRIVATE
    src/main.cpp
)

target_link_libraries(chimera_host PRIVATE host_lib)

set_target_properties(chimera_host
    PROPERTIES
        OUTPUT_NAME chimera
)