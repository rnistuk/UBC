cmake_minimum_required(VERSION 3.26)
project(BridsonUBC)

set(CMAKE_CXX_STANDARD 23)

INCLUDE(FindPkgConfig)

# SDL2 - install SDL2 with 'brew install sdl2'
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDEDIR})
link_directories(${SDL2_LIBRARY_DIRS})

# This project uses the GoogleTest framework for unit testing, this section
# downloads the GoogleTest library from the Google github repo
include(ExternalProject)
ExternalProject_Add(googletest
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}/googletest"
        URL https://github.com/google/googletest/archive/release-1.8.1.tar.gz
        URL_HASH SHA256=9bf1fe5182a604b4135edc1a425ae356c9ad15e9b23f9f12a02e80184c3a249c
        TIMEOUT 30
        DOWNLOAD_NO_PROGRESS true
        INSTALL_COMMAND "")

ExternalProject_Get_Property(googletest SOURCE_DIR)
include_directories(${SOURCE_DIR}/googlemock/include ${SOURCE_DIR}/googletest/include)
ExternalProject_Get_Property(googletest BINARY_DIR)
link_directories(${BINARY_DIR}/googlemock ${BINARY_DIR}/googlemock/gtest)
set(GMOCK_BOTH_LIBRARIES gmock_main gmock gtest)
set_property(DIRECTORY PROPERTY CLEAN_NO_CUSTOM "${CMAKE_CURRENT_BINARY_DIR}/googletest")
unset(SOURCE_DIR)
unset(BINARY_DIR)

# Add the demo subdirectory
add_subdirectory(FastPoisson)
#add_subdirectory(unittests)