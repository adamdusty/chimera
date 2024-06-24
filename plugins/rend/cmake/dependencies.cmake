include(FetchContent)

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