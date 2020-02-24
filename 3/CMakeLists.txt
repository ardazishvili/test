cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
project(math)

add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
add_executable(math
  main.cpp
  Matrix.h
  Matrix.cpp
  Vector.h
  )

add_executable(unit_tests tests/unit_main.cpp
  tests/Vector_tests.cpp
  tests/Utilities_tests.cpp
  )
target_link_libraries(unit_tests gtest gmock)
