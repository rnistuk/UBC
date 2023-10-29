enable_testing()
include(GoogleTest)

add_executable(FPoissonTest ../FastPoisson/Bridson.cpp ../FastPoisson/BridsonTest.cpp)

add_dependencies(FPoissonTest googletest)
target_link_libraries(FPoissonTest ${GMOCK_BOTH_LIBRARIES})
target_include_directories(FPoissonTest PRIVATE ../FastPoisson)
gtest_discover_tests(FPoissonTest)