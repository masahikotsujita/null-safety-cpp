cmake_minimum_required(VERSION 4.0)
project(null-safety LANGUAGES CXX)

option(NULLSAFETY_BUILD_EXAMPLES "Build examples" OFF)

add_library(null-safety STATIC
    include/null-safety/pointer/nullable_ptr.h
    include/null-safety/pointer/nonull_ptr.h
    include/null-safety/null-safety.h
    src/null-safety.cpp
)
target_include_directories(null-safety PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(null-safety PUBLIC cxx_std_17)

if(NULLSAFETY_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()