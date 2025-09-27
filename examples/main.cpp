#include <cassert>
#include <null-safety/null-safety.h>
#include <string>

int main(int argc, char* argv[]) {
    nsf::nullable_ptr<std::string> fooNull;
    // cannot compile
    // printf("foo(maybe null) %s\n", fooNull->c_str());

    fooNull.if_nonnull([&](const nsf::nonnull_ptr<std::string>& foo) {
        printf("foo(maybe null): %s\n", foo->c_str());
    }, [&]{
        printf("foo(maybe null): null\n");
    });

    nsf::nullable_ptr<std::string> fooNonNull = nsf::make_nonnull<std::string>("foo");
    fooNonNull.if_nonnull([&](const nsf::nonnull_ptr<std::string>& foo) {
        printf("foo(maybe nonnull): %s\n", foo->c_str());
    });

    nsf::nonnull_ptr<std::string> fooNonNullForce = fooNonNull.nonnull_force();
    printf("foo(force unwrapped): %s\n", fooNonNullForce->c_str());

    nsf::nonnull_ptr<std::string> barNonNull = nsf::make_nonnull<std::string>("bar");
    printf("bar(nonnull): %s\n", barNonNull->c_str());

    return 0;
}
