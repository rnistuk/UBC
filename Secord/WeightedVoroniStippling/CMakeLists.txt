project(WeightedVoroniStippling)

add_executable(wvs
        main.cpp
        SDLGraphics.cpp)

target_link_libraries(wvs ${SDL2_LINK_LIBRARIES})