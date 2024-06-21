include(FetchContent)

FetchContent_Declare(
    sdl3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        6e53a364141d6f5e95bfd805982a9b137bd5463d # main 6/20/24
    SYSTEM
)

FetchContent_MakeAvailable(sdl3)