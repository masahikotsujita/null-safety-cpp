//
// Created by masahiko on 2025/09/27.
//

#include <catch2/catch_all.hpp>
#include <null-safety/null_safety.h>
#include "utility/type_traits.h"
#include "utility/utility.h"

using namespace nsf_test;

SCENARIO("nullable_ptr constructors correctly works", "[nullable_ptr]") {
    GIVEN("a default-constructed nullable pointer") {
        nsf::nullable_ptr<int> a;
        THEN("it is null") {
            REQUIRE(a == nullptr);
            REQUIRE(nullptr == a);
            REQUIRE_FALSE(a != nullptr);
            REQUIRE_FALSE(nullptr != a);
            REQUIRE_FALSE(bool(a));
        }
        THEN("use_count is 0") {
            REQUIRE(a.use_count() == 0);
        }
    }
    GIVEN("a nullable pointer constructed from nullptr") {
        nsf::nullable_ptr<int> a = nullptr;
        THEN("it is null") {
            REQUIRE(a == nullptr);
            REQUIRE(nullptr == a);
            REQUIRE_FALSE(a != nullptr);
            REQUIRE_FALSE(nullptr != a);
            REQUIRE_FALSE(bool(a));
        }
        THEN("use_count is 0") {
            REQUIRE(a.use_count() == 0);
        }
    }
    GIVEN("two null nullable pointers") {
        nsf::nullable_ptr<int> a;
        nsf::nullable_ptr<int> b = nullptr;
        THEN("they are equal") {
            REQUIRE(a == b);
        }
    }
    GIVEN("a nullable pointer constructed from nonnull pointer") {
        nsf::nullable_ptr<int> a = nsf::make_nonnull<int>(1);
        THEN("it is not null") {
            REQUIRE_FALSE(a == nullptr);
            REQUIRE_FALSE(nullptr == a);
            REQUIRE(a != nullptr);
            REQUIRE(nullptr != a);
            REQUIRE(bool(a));
        }
        THEN("use_count is 1") {
            REQUIRE(a.use_count() == 1);
        }
    }
}

SCENARIO("unwrapping nullable pointer correctly works", "[nullable_ptr]") {
    GIVEN("a null nullable_ptr") {
        nsf::nullable_ptr<int> a = nullptr;
        WHEN("unwrap using if_nonnull") {
            int then_invoke_count = 0;
            a.if_nonnull([&](const auto&) {
                then_invoke_count++;
            });
            THEN("then block is not invocated.") {
                REQUIRE(then_invoke_count == 0);
            }
        }
        WHEN("unwrap using if_nonnull_else") {
            int then_invoke_count = 0;
            int else_invoke_count = 0;
            a.if_nonnull([&](const auto&) {
                then_invoke_count++;
            }, [&] {
                else_invoke_count++;
            });
            THEN("else block is invocated only once.") {
                REQUIRE(then_invoke_count == 0);
                REQUIRE(else_invoke_count == 1);
            }
        }
    }
    GIVEN("a non-null nullable_ptr") {
        nsf::nullable_ptr<int> a = nsf::make_nonnull<int>(1);
        WHEN("unwrap using nonnull_force") {
            auto nonnull_a = a.nonnull_force();
            THEN("unwrap correctly") {
                REQUIRE(*nonnull_a == 1);
            }
        }
        WHEN("unwrap using if_nonnull") {
            int then_invoke_count = 0;
            a.if_nonnull([&](const auto&) {
                then_invoke_count++;
            });
            THEN("then block is not invocated.") {
                REQUIRE(then_invoke_count == 1);
            }
        }
        WHEN("unwrap using if_nonnull_else") {
            int then_invoke_count = 0;
            int else_invoke_count = 0;
            a.if_nonnull([&](const auto&) {
                then_invoke_count++;
            }, [&] {
                else_invoke_count++;
            });
            THEN("else block is invocated only once.") {
                REQUIRE(then_invoke_count == 1);
                REQUIRE(else_invoke_count == 0);
            }
        }
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
