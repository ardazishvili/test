cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
project(ci_string)

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
add_executable(ci_string main
                         Text.h
                         Text.cpp)
target_link_libraries(ci_string stdc++fs)

add_executable(unit_tests tests/unit_main.cpp
                          tests/Utilities_tests.cpp
                          tests/Text_tests.cpp
                          Text.h
                          Text.cpp)
target_link_libraries(unit_tests gtest gmock stdc++fs)
