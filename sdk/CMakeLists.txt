cmake_minimum_required(VERSION 3.29)

project(
    chimera_sdk
    VERSION 0.1.0
    DESCRIPTION "A short description"
    LANGUAGES CXX
)

# Include utilities
include(cmake/options.cmake)
include(cmake/warning-guard.cmake)
include(cmake/compile-options.cmake)
include(cmake/dependencies.cmake)

# Declare library
add_library(chimera_sdk SHARED)
add_library(chimera::sdk ALIAS chimera_sdk)

# Generate header for export
include(GenerateExportHeader)
generate_export_header(
    chimera_sdk
    BASE_NAME chimera
    EXPORT_FILE_NAME include/chimera/export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

# Add sources
target_sources(chimera_sdk PRIVATE
    src/sdk.cpp
    src/flecs/flecs.c
)

# Add include directory
# warning_guard adds SYSTEM modifier if the project isn't top level
target_include_directories(chimera_sdk ${warning_guard}
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(chimera_sdk
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
)

# Include and link dependencies
# target_link_libraries(chimera_sdk PUBLIC flecs::flecs_static)

# Add compile options
add_dev_compile_opts(chimera_sdk)
target_compile_definitions(chimera_sdk PUBLIC flecs_EXPORTS)


# Set properties
set_target_properties(
    chimera_sdk PROPERTIES
    CXX_VISIBILITY_PRESET "hidden"
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME chimerasdk
    OUTPUT_NAME chimerasdk
)

# Install rules
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()