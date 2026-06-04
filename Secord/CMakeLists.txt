project(Secord)

set(CMAKE_CXX_STANDARD 23)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDEDIR})
link_directories(${SDL2_LIBRARY_DIRS})

add_subdirectory(WeightedVoroniStippling)
