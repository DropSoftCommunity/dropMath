cmake_minimum_required(VERSION 3.10)

project(drop_math_test VERSION 0.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(drop_math_test test.cpp)

configure_file(config.h.in config.h)

target_include_directories(drop_math_test PUBLIC "${PROJECT_BINARY_DIR}")


