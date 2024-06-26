cmake_minimum_required(VERSION 3.29)

project(chimera)

add_subdirectory(sdk)
add_subdirectory(host)

add_subdirectory(plugins/core)
add_subdirectory(plugins/rend)

include(cmake/package.cmake)

if(BUILD_TESTING)
    include(cmake/integration.cmake)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
    add_subdirectory(tests/integration)
endif()
