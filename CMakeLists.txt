cmake_minimum_required(VERSION 3.10)
project(dropMath VERSION 1.0.0 LANGUAGES CXX)

option(DROPMATH_BUILD_TESTS "Build Tests" OFF)
option(DROPMATH_BUILD_EXAMPLES "Build Examples" OFF)

add_library(dropMath INTERFACE)
add_library(dropMath::dropMath ALIAS dropMath)

target_compile_features(dropMath INTERFACE cxx_std_17)

target_include_directories(dropMath
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Installation
install(
    TARGETS dropMath
    EXPORT dropMathTargets
)

install(
    EXPORT dropMathTargets
    NAMESPACE dropMath::
    DESTINATION lib/cmake/dropMath
)

install(
    DIRECTORY include/
    DESTINATION include
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/dropMathConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/dropMathConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/dropMathConfig.cmake
    INSTALL_DESTINATION lib/cmake/dropMath
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/dropMathConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/dropMathConfigVersion.cmake
    DESTINATION lib/cmake/dropMath
)

if(DROPMATH_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(DROPMATH_BUILD_TESTS)
  add_subdirectory(test)
endif()
