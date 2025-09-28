//
// Created by masahiko on 2025/09/29.
//

#ifndef NULL_SAFETY_TEST_TYPE_TRAITS_H
#define NULL_SAFETY_TEST_TYPE_TRAITS_H

namespace nsf_test {
// C++20のequality_comparable代替
// C++20に移行後削除

// == 比較可能かどうかをチェックします
template<typename T, typename U, typename = std::void_t<> >
struct is_eq_comparable_with_t : std::false_type {
};

template<typename T, typename U>
struct is_eq_comparable_with_t<T, U, std::void_t<decltype(std::declval<const T &>() == std::declval<const U &>()
    )> > : std::true_type {
};

// != 比較可能かどうかをチェックします
template<typename T, typename U, typename = std::void_t<> >
struct is_ne_comparable_with_t : std::false_type {
};

template<typename T, typename U>
struct is_ne_comparable_with_t<T, U, std::void_t<decltype(std::declval<const T &>() != std::declval<const U &>()
    )> > : std::true_type {
};

// 相互に==比較、!=比較可能かどうかをチェックします
template<typename T, typename U>
using is_equality_comparable_with_t = std::conjunction<
    is_eq_comparable_with_t<T, U>,
    is_eq_comparable_with_t<U, T>,
    is_ne_comparable_with_t<T, U>,
    is_ne_comparable_with_t<U, T>
>;
template<typename T, typename U>
constexpr bool is_equality_comparable_with_v = is_equality_comparable_with_t<T, U>::value;

template<typename T>
using is_equality_comparable_t = is_equality_comparable_with_t<T, T>;
template<typename T>
constexpr bool is_equality_comparable_v = is_equality_comparable_t<T>::value;

// *、-> 演算子があるかどうか調べます

// *演算子があるかどうかをチェックします
// (注)現状生ポインタに対して正常に動かない。生ポインタの*は組み込み演算子であってメンバ関数ではないため．
template<typename T, typename = void>
struct has_dereference_t : std::false_type {
};

template<typename T>
struct has_dereference_t<T, std::void_t<decltype(std::declval<T>().operator*())> > : std::true_type {
};

template<typename T>
constexpr bool has_dereference_v = has_dereference_t<T>::value;

// ->演算子があるかどうかをチェックします
// (注)現状生ポインタに対して正常に動かない。生ポインタの->は組み込み演算子であってメンバ関数ではないため．
template<typename T, typename = void>
struct has_arrow_t : std::false_type {
};

template<typename T>
struct has_arrow_t<T, std::void_t<decltype(std::declval<T>().operator->())> > : std::true_type {
};

template<typename T>
constexpr bool has_arrow_v = has_arrow_t<T>::value;
}

#endif //NULL_SAFETY_TEST_TYPE_TRAITS_H
