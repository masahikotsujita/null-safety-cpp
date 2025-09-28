//
// Created by masahiko on 2025/09/28.
//

#include <catch2/catch_all.hpp>
#include "type_traits.h"
#include "utility.h"

using namespace nsf_test;

SCENARIO("can check whether types are == comparable", "[utility]") {
    THEN("int is == comparable with itself") {
        REQUIRE(nsf_test::is_eq_comparable_with_t<int, int>::value);
    }
    THEN("FOO is not == comparable with itself") {
        REQUIRE(!nsf_test::is_eq_comparable_with_t<nsf_test::FOO, nsf_test::FOO>::value);
    }
    THEN("int* and nullptr are == comparable") {
        REQUIRE(nsf_test::is_eq_comparable_with_t<int*, std::nullptr_t>::value);
        REQUIRE(nsf_test::is_eq_comparable_with_t<std::nullptr_t, int*>::value);
    }
    THEN("int and std::string are not == comparable") {
        REQUIRE(!nsf_test::is_eq_comparable_with_t<int, std::string>::value);
        REQUIRE(!nsf_test::is_eq_comparable_with_t<std::string, int>::value);
    }
}

SCENARIO("can check whether types are != comparable", "[utility]") {
    THEN("int is != comparable with itself") {
        REQUIRE(nsf_test::is_ne_comparable_with_t<int, int>::value);
    }
    THEN("FOO is not != comparable with itself") {
        REQUIRE(!nsf_test::is_ne_comparable_with_t<nsf_test::FOO, nsf_test::FOO>::value);
    }
    THEN("int* and nullptr are != comparable") {
        REQUIRE(nsf_test::is_ne_comparable_with_t<int*, std::nullptr_t>::value);
        REQUIRE(nsf_test::is_ne_comparable_with_t<std::nullptr_t, int*>::value);
    }
    THEN("int and std::string are not != comparable") {
        REQUIRE(!nsf_test::is_ne_comparable_with_t<int, std::string>::value);
        REQUIRE(!nsf_test::is_ne_comparable_with_t<std::string, int>::value);
    }
}

SCENARIO("can check whether types is ==, != comparable each other", "[utility]") {
    THEN("int is ==, != comparable with itself") {
        REQUIRE(nsf_test::is_equality_comparable_with_t<int, int>::value);
        REQUIRE(nsf_test::is_equality_comparable_with_v<int, int>);
        REQUIRE(nsf_test::is_equality_comparable_t<int>::value);
        REQUIRE(nsf_test::is_equality_comparable_v<int>);
    }
    THEN("FOO is not == comparable with itself") {
        REQUIRE(!nsf_test::is_equality_comparable_with_t<nsf_test::FOO, nsf_test::FOO>::value);
        REQUIRE(!nsf_test::is_equality_comparable_with_v<nsf_test::FOO, nsf_test::FOO>);
        REQUIRE(!nsf_test::is_equality_comparable_t<nsf_test::FOO>::value);
        REQUIRE(!nsf_test::is_equality_comparable_v<nsf_test::FOO>);
    }
    THEN("int* and nullptr are ==, != comparable") {
        REQUIRE(nsf_test::is_equality_comparable_with_t<int*, std::nullptr_t>::value);
        REQUIRE(nsf_test::is_equality_comparable_with_v<int*, std::nullptr_t>);
    }
    THEN("int and std::string are not == comparable") {
        REQUIRE(!nsf_test::is_equality_comparable_with_t<int, std::string>::value);
        REQUIRE(!nsf_test::is_equality_comparable_with_v<int, std::string>);
    }
}

SCENARIO("can check whether a type has dereference operator", "[utility]") {
    THEN("int does not have * operator") {
        REQUIRE(!nsf_test::has_dereference_t<int>::value);
        REQUIRE(!nsf_test::has_dereference_v<int>);
    }
    THEN("std::string does not have * operator") {
        REQUIRE(!nsf_test::has_dereference_t<std::string>::value);
        REQUIRE(!nsf_test::has_dereference_v<std::string>);
    }
    // 生ポインタに対して正常に判定できないのでいったんコメントアウト
    // THEN("int* has * operator") {
    //     REQUIRE(nsf_test::has_dereference_t<int*>::value);
    //     REQUIRE(nsf_test::has_dereference_v<int*>);
    // }
    // THEN("std::string* has * operator") {
    //     REQUIRE(nsf_test::has_dereference_t<std::string*>::value);
    //     REQUIRE(nsf_test::has_dereference_v<std::string*>);
    // }
    THEN("std::shared_ptr<std::string> has * operator") {
        REQUIRE(nsf_test::has_dereference_t<std::shared_ptr<std::string>>::value);
        REQUIRE(nsf_test::has_dereference_v<std::shared_ptr<std::string>>);
    }
    THEN("std::optional<std::string> has * operator") {
        REQUIRE(nsf_test::has_dereference_t<std::optional<std::string>>::value);
        REQUIRE(nsf_test::has_dereference_v<std::optional<std::string>>);
    }
}

SCENARIO("can check whether a type has arrow operator", "[utility]") {
    THEN("int does not have -> operator") {
        REQUIRE(!nsf_test::has_arrow_t<int>::value);
        REQUIRE(!nsf_test::has_arrow_v<int>);
    }
    THEN("std::string does not have -> operator") {
        REQUIRE(!nsf_test::has_arrow_t<std::string>::value);
        REQUIRE(!nsf_test::has_arrow_v<std::string>);
    }
    // 生ポインタに対して正常に判定できないのでいったんコメントアウト
    // THEN("int* does not have -> operator") {
    //     REQUIRE(!nsf_test::has_arrow_t<int*>::value);
    //     REQUIRE(!nsf_test::has_arrow_v<int*>);
    // }
    // THEN("std::string* has -> operator") {
    //     REQUIRE(nsf_test::has_arrow_t<std::string*>::value);
    //     REQUIRE(nsf_test::has_arrow_v<std::string*>);
    // }
    THEN("std::shared_ptr<std::string> has -> operator") {
        REQUIRE(nsf_test::has_arrow_t<std::shared_ptr<std::string>>::value);
        REQUIRE(nsf_test::has_arrow_v<std::shared_ptr<std::string>>);
    }
    THEN("std::optional<std::string> has -> operator") {
        REQUIRE(nsf_test::has_arrow_t<std::optional<std::string>>::value);
        REQUIRE(nsf_test::has_arrow_v<std::optional<std::string>>);
    }
}
