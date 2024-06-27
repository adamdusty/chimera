include(FetchContent)

set(ECHIDNA_BUILD_TESTS OFF)
set(ECHIDNA_BUILD_SAMPLES OFF)
FetchContent_Declare(
    echidna
    GIT_REPOSITORY  https://github.com/adamdusty/echidna.git
    GIT_TAG         main
    GIT_SHALLOW
    SYSTEM
)

FetchContent_MakeAvailable(echidna)

set_target_properties(echidna_echidna
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)