cmake_minimum_required(VERSION 3.10)

project(drop_math_test VERSION 0.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(drop_math_test test.cpp)

target_link_libraries(drop_math_test PRIVATE dropMath::dropMath)
