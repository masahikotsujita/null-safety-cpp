//
// Created by masahiko on 2025/09/27.
//

#include <catch2/catch_all.hpp>
#include <null-safety/null-safety.h>
#include "utility/type_traits.h"
#include "utility/utility.h"

using namespace nsf_test;

SCENARIO("nullable pointers are equality comparable", "[nullable_ptr]") {
    THEN("equality comparable with itself") {
        REQUIRE(nsf_test::is_equality_comparable_v<nsf::nullable_ptr<FOO>>);
    }
    THEN("equality comparable with nullptr") {
        REQUIRE(nsf_test::is_equality_comparable_with_v<nsf::nullable_ptr<FOO>, std::nullptr_t>);
    }
}

SCENARIO("a nullable pointer cannot access its resource without null-check", "[nullable_ptr]") {
    THEN("cannot call * operator") {
        REQUIRE(!nsf_test::has_dereference_v<nsf::nullable_ptr<FOO>>);
    }
    THEN("cannot call -> operator") {
        REQUIRE(!nsf_test::has_arrow_v<nsf::nullable_ptr<FOO>>);
    }
}

SCENARIO("a nullable pointer can access null-check", "[nullable_ptr]") {
    GIVEN("a null nullable pointer") {
        nsf::nullable_ptr<FOO> foo = nullptr;
        WHEN("unwrap using if_nonnull") {
            bool flag = false;;
            foo.if_nonnull([&](const auto &) {
                flag = true;
            });
            THEN("cannot unwrap") {
                REQUIRE(!flag);
            }
        }
    }
    GIVEN("a nonnull nullable pointer") {
        nsf::nullable_ptr<FOO> foo = nsf::make_nonnull<FOO>(1, 2);
        WHEN("unwrap using if_nonnull") {
            bool flag = false;
            int a = 0;
            int b = 0;
            foo.if_nonnull([&](const auto &nonnullFoo) {
                flag = true;
                a = nonnullFoo->a;
                b = nonnullFoo->b;
            });
            THEN("unwrapped correctly") {
                REQUIRE(flag);
                REQUIRE(a == 1);
                REQUIRE(b == 2);
            }
        }
        WHEN("force unwrapped") {
            auto nonnullFoo = foo.nonnull_force();
            THEN("unwrapped correctly") {
                REQUIRE(nonnullFoo->a == 1);
                REQUIRE(nonnullFoo->b == 2);
            }
        }
    }
}
