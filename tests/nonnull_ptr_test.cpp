//
// Created by masahiko on 2025/09/27.
//

#include <catch2/catch_all.hpp>
#include <null-safety/null-safety.h>
#include "utility/type_traits.h"
#include "utility/utility.h"

using namespace nsf_test;

SCENARIO("nonnull_ptr cannot be created from potentially nullable pointers", "[nonnull_ptr]") {
    THEN("cannot be default-constructed") {
        REQUIRE(!std::is_default_constructible_v<nsf::nonnull_ptr<FOO>>);
    }
    THEN("cannot be constructed from nullptr") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, std::nullptr_t>);
    }
    THEN("cannot be constructed from nullopt") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, std::nullopt_t>);
    }
    THEN("cannot be constructed from raw pointer") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, FOO*>);
    }
    THEN("cannot be constructed from shared_ptr") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, std::shared_ptr<FOO>>);
    }
    THEN("cannot be constructed from weak_ptr") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, std::weak_ptr<FOO>>);
    }
    THEN("cannot be constructed from unique_ptr") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, std::unique_ptr<FOO>>);
    }
    THEN("cannot be constructed from nullable_ptr") {
        REQUIRE(!std::is_constructible_v<nsf::nonnull_ptr<FOO>, nsf::nullable_ptr<FOO>>);
    }
}

SCENARIO("nonnull pointer can access its resource") {
    GIVEN("a nonnull pointer") {
        nsf::nonnull_ptr<FOO> foo = nsf::make_nonnull<FOO>(1, 2);
        THEN("can read its data by -> operator") {
            REQUIRE(foo->a == 1);
            REQUIRE(foo->b == 2);
        }
        THEN("can read its data by * operator") {
            REQUIRE((*foo).a == 1);
            REQUIRE((*foo).b == 2);
        }
        THEN("can read its data by get()") {
            REQUIRE(foo.get()->a == 1);
            REQUIRE(foo.get()->b == 2);
        }
        THEN("can read its data by shared()") {
            REQUIRE(foo.shared()->a == 1);
            REQUIRE(foo.shared()->b == 2);
        }
        WHEN("write its data by -> operator") {
            foo->a = 10;
            THEN("can read it") {
                REQUIRE(foo->a == 10);
            }
        }
        WHEN("write its data by * operator") {
            (*foo).a = 10;
            THEN("can read it") {
                REQUIRE(foo->a == 10);
            }
        }
        WHEN("write its data by get()") {
            foo.get()->a = 10;
            THEN("can read it") {
                REQUIRE(foo->a == 10);
            }
        }
        WHEN("write its data by shared()") {
            foo.shared()->a = 10;
            THEN("can read it") {
                REQUIRE(foo->a == 10);
            }
        }
    }
}
