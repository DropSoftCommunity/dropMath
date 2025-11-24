cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(examples examples.cpp)

target_link_libraries(examples PRIVATE dropMath::dropMath)
