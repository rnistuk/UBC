project(FPoisson)
add_executable(FPoisson
        src/main.cpp
        src/SDLGraphics.cpp
        src/SDLGraphics.h
        src/Utilities.cpp
        src/Utilities.h
        src/Bridson.cpp
        src/Bridson.h)

target_link_libraries(FPoisson ${SDL2_LINK_LIBRARIES})
