cmake_minimum_required(VERSION 3.15)
project(dropMath_examples)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} examples.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

