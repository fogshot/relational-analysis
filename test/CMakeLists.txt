cmake_minimum_required(VERSION 2.8)

#Add the google test subdirectory
add_subdirectory(googletest)

#include googletest/include dir
include_directories(googletest/googletest/include)

#include the googlemock/include dir
include_directories(googletest/googlemock/include)

#Define your executable
add_executable(gmain gmain.cpp)

#Link with GoogleTest
target_link_libraries(gmain gtest gtest_main)

#Link with GoogleMock
target_link_libraries(gmain gmock gmock_main)