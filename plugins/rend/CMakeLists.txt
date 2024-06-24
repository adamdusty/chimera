cmake_minimum_required(VERSION 3.29)

project(
    chimera_rend
    VERSION 0.1.0
    DESCRIPTION "A short description"
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(chimera_rend SHARED)
add_library(chimera::rend ALIAS chimera_rend)

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    chimera_rend
    BASE_NAME chimera
    EXPORT_FILE_NAME include/chimera/rend/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Add sources
target_sources(chimera_rend PRIVATE
    src/rend.cpp
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(chimera_rend ${warning_guard}
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(chimera_rend SYSTEM
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

# Include and link dependencies
target_link_libraries(chimera_rend PUBLIC chimera::sdk echidna::echidna)

# Add compile options
add_dev_compile_opts(chimera_rend)


# Set properties
set_target_properties(
    chimera_rend PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    PREFIX ""
    EXPORT_NAME rend
    OUTPUT_NAME rend
)

add_custom_command(TARGET chimera_rend POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/plugin.json ${CMAKE_CURRENT_BINARY_DIR}
)

# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
#   include(cmake/install-rules.cmake)
endif()