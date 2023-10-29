add_executable(FPoisson main.cpp
        SDLGraphics.cpp
        SDLGraphics.h
        Utilities.cpp
        Utilities.h
        Bridson.cpp
        Bridson.h)

target_link_libraries(FPoisson ${SDL2_LINK_LIBRARIES})
