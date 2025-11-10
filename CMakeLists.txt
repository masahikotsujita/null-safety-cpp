cmake_minimum_required(VERSION 3.12)
project(null_safety LANGUAGES CXX)

option(NULLSAFETY_BUILD_TESTS "Build tests" ON)
option(NULLSAFETY_BUILD_EXAMPLES "Build examples" OFF)

add_library(null_safety STATIC
    include/null_safety/pointer/nullable_ptr.h
    include/null_safety/pointer/nonull_ptr.h
    include/null_safety/null_safety.h
    src/null_safety.cpp
)
target_include_directories(null_safety PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(null_safety PUBLIC cxx_std_17)

if(NULLSAFETY_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(NULLSAFETY_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()