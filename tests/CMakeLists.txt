cmake_minimum_required(VERSION 3.29)

project(
    chimeraTests
    LANGUAGES CXX
)

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
    src/host_tests.cpp
    src/sdk_tests.cpp
    src/rend_tests.cpp
)

# Link libs
target_link_libraries(chimera_tests 
    PUBLIC
        host_lib
        chimera::sdk
        chimera::rend
        snitch::snitch
)

# Add test
add_test(NAME chimera_tests COMMAND chimera_tests)


# TODO: Fix test properties for windows
#       Some libs will always be shared libraries no matter the cmake configuration
# Enable test binary to find the DLL if building a shared lib
if(BUILD_SHARED_LIBS)
    set_tests_properties(chimera_tests PROPERTIES
        ENVIRONMENT_MODIFICATION
            "PATH=path_list_append:$<TARGET_FILE_DIR:chimera::sdk>;PATH=path_list_append:$<TARGET_FILE_DIR:chimera::rend>;PATH=path_list_append:$<TARGET_FILE_DIR:snitch::snitch>"
    )
endif()
