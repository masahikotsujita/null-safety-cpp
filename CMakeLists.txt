cmake_minimum_required(VERSION 4.0)
project(null-safety LANGUAGES CXX)

add_library(null-safety STATIC
    include/null-safety/nullable_ptr.h
    include/null-safety/nonull_ptr.h
    include/null-safety/null-safety.h
    src/null-safety.cpp
)
target_include_directories(null-safety PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(null-safety PUBLIC cxx_std_17)