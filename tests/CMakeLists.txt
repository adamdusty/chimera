cmake_minimum_required(VERSION 3.29)

project(
    chimeraTests
    LANGUAGES CXX
)

# If test project is built independently, find the project package
if(PROJECT_IS_TOP_LEVEL)
    find_package(chimerasdk REQUIRED)
    enable_testing()
endif()

# Get the testing library
include(FetchContent)
FetchContent_Declare(
    snitch
    GIT_REPOSITORY https://github.com/snitch-org/snitch.git
    GIT_TAG        v1.2.5
    SYSTEM
)
FetchContent_MakeAvailable(snitch)

# Add test exe
add_executable(chimera_tests)

# Add test sources
target_sources(chimera_tests PRIVATE
    sdk/tests.cpp
    host/tests.cpp
)

# Link libs
target_link_libraries(chimera_tests PRIVATE host_lib chimera::sdk snitch::snitch)

# Add test
add_test(NAME chimera_tests COMMAND chimera_tests)

# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(chimera_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:chimera::sdk>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>"
    )
endif()
