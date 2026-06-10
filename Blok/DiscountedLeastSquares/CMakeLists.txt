project(dlsfit)
enable_testing()
include(GoogleTest)

add_executable(dlsfit
        src/main.cpp)

#add_executable(dlsfitTest src/something.cpp)
#target_link_libraries(dlsfitTest ${GMOCK_BOTH_LIBRARIES})
#target_include_directories(dlsfitTest PRIVATE ./src)
#gtest_discover_tests(dlsfitTest)

