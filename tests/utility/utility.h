//
// Created by masahiko on 2025/09/28.
//

#ifndef NULL_SAFETY_TEST_UTILITY_H
#define NULL_SAFETY_TEST_UTILITY_H

namespace nsf_test {
struct FOO {
    FOO(int a, int b) : a(a), b(b) {
    }

    int a;
    int b;
};

struct BAR : FOO {
    BAR(int a, int b, int c) : FOO(a, b), c(c) {
    }

    int c;
};
}

#endif //NULL_SAFETY_TEST_UTILITY_H
