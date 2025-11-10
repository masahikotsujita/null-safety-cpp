# Catch2を使用
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.10.0
)
FetchContent_MakeAvailable(Catch2)

# テスト
add_executable(null_safety_tests
    nullable_ptr_test.cpp
    nonnull_ptr_test.cpp
    utility/utility.h
    utility/type_traits_test.cpp
    utility/type_traits.h
)
target_link_libraries(null_safety_tests PRIVATE null_safety Catch2::Catch2WithMain)
add_test(NAME null_safety_tests COMMAND null_safety_tests)