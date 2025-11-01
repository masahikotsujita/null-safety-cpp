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

SCENARIO("nonnull_ptr is not equatable with null", "[nonnull_ptr]") {
    THEN("equality comparable with nullptr") {
        REQUIRE(!nsf_test::is_equality_comparable_with_v<nsf::nonnull_ptr<FOO>, std::nullptr_t>);
    }
    THEN("equality comparable with nullptr") {
        REQUIRE(!nsf_test::is_equality_comparable_with_v<nsf::nonnull_ptr<FOO>, std::nullopt_t>);
    }
}

SCENARIO("nonnull_ptr constructed correctly") {
    GIVEN("a nonnull pointer copy-constructed from an another nonnull pointer") {
        nsf::nonnull_ptr<int> a = nsf::make_nonnull<int>(1);
        nsf::nonnull_ptr<int> b = a;
        THEN("it should be correctly copied") {
            REQUIRE(*a == 1);
            REQUIRE(*b == 1);
        }
        WHEN("the source pointer is replaced by another pointer") {
            a = nsf::make_nonnull<int>(2);
            THEN("it does not affect the destination pointer") {
                REQUIRE(*b == 1);
            }
        }
    }
    GIVEN("a nonnull pointer copy-assigned from an another nonnull pointer") {
        nsf::nonnull_ptr<int> a = nsf::make_nonnull<int>(1);
        nsf::nonnull_ptr<int> b = nsf::make_nonnull<int>(0);
        b = a;
        THEN("it should be correctly copied") {
            REQUIRE(*a == 1);
            REQUIRE(*b == 1);
        }
        WHEN("the source pointer is replaced by another pointer") {
            a = nsf::make_nonnull<int>(2);
            THEN("it does not affect the destination pointer") {
                REQUIRE(*b == 1);
            }
        }
    }
    GIVEN("a nonnull pointer move-constructed from an another nonnull pointer") {
        nsf::nonnull_ptr<int> a = nsf::make_nonnull<int>(1);
        nsf::nonnull_ptr<int> b = std::move(a);
        THEN("it should be correctly moved") {
            REQUIRE(*b == 1);
        }
    }
    GIVEN("a nonnull pointer move-assigned from an another nonnull pointer") {
        nsf::nonnull_ptr<int> a = nsf::make_nonnull<int>(1);
        nsf::nonnull_ptr<int> b = nsf::make_nonnull<int>(0);
        b = std::move(a);
        THEN("it should be correctly moved") {
            REQUIRE(*b == 1);
        }
    }
}

SCENARIO("nonnull pointer can access its resource", "[nonnull_ptr]") {
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

SCENARIO("copying nonnull_ptr increase its use_count", "[nonnull_ptr]") {
    GIVEN("a nonnull_ptr") {
        std::optional optFoo = nsf::make_nonnull<FOO>(1, 2);
        nsf::nonnull_ptr<FOO>& foo = optFoo.value();
        THEN("use count is 1") {
            REQUIRE(foo.use_count() == 1);
        }
        WHEN("it's copied to another nonnull ptr") {
            nsf::nonnull_ptr<FOO> foo2 = foo;
            THEN("use count is 2") {
                REQUIRE(foo.use_count() == 2);
                REQUIRE(foo2.use_count() == 2);
            }
            WHEN("the source pointer is destructed") {
                optFoo.reset();
                THEN("use count is 1") {
                    REQUIRE(foo.use_count() == 1);
                }
            }
            WHEN("the source pointer replaced by another pointer") {
                optFoo.value() = nsf::make_nonnull<FOO>(3, 4);
                THEN("use count is 1") {
                    REQUIRE(foo.use_count() == 1);
                }
            }
        }
        WHEN("it's moved to another nonnull ptr") {
            nsf::nonnull_ptr<FOO> foo2 = std::move(foo);
            THEN("use count is 1") {
                REQUIRE(foo2.use_count() == 1);
            }
        }
    }
}
