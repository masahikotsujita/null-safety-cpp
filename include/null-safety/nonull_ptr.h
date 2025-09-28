//
// Created by masahiko on 2025/09/27.
//

#ifndef NULL_SAFETY_CPP_NONULL_PTR_H
#define NULL_SAFETY_CPP_NONULL_PTR_H
#include <memory>

#include "nullable_ptr.h"

namespace nsf {
template<typename T>
class nullable_ptr;

template<typename T>
class nonnull_ptr final {
public:
    /// 要素型
    using element_type = T;
    /// 非NULLポインタ型
    using nullable_type = nullable_ptr<T>;
    /// weakポインタ型
    using weak_type = std::weak_ptr<T>;

    friend class nullable_ptr<T>;
    template<typename Y>
    friend class nonnull_ptr;

    template<typename U, typename... Args>
    friend nonnull_ptr<U> make_nonnull(Args &&...);

    nonnull_ptr() = delete;

    /**
     * コピーコンストラクタ
     * @param r コピー元ポインタ
     */
    nonnull_ptr(const nonnull_ptr &r) noexcept
        : m_sp(r.m_sp) {
    }

    /**
     * コピーコンストラクタ
     * @tparam Y コピー元ポインタの要素型
     * @param r コピー元ポインタ
     */
    template<typename Y>
    nonnull_ptr(const nonnull_ptr<Y> &r) noexcept
        : m_sp(r.m_sp) {
    }

    /**
     * ムーブコンストラクタ
     * @param r ムーブ元ポインタ
     */
    nonnull_ptr(nonnull_ptr &&r) noexcept
        : m_sp(std::move(r.m_sp)) {
    }

    /**
     * ムーブコンストラクタ
     * @tparam Y ムーブ元ポインタの要素型
     * @param r ムーブ元ポインタ
     */
    template<typename Y>
    nonnull_ptr(nonnull_ptr<Y> &&r) noexcept
        : m_sp(std::move(r.m_sp)) {
    }

    /**
     * コピー代入演算子
     * @tparam Y コピー元ポインタの要素型
     * @param r コピー元ポインタ
     * @return このポインタ
     */
    template<typename Y>
    nonnull_ptr &operator=(const nonnull_ptr<Y> &r) noexcept {
        m_sp = r.shared();
        return *this;
    }

    /**
     * ムーブ代入演算子
     * @tparam Y ムーブ元ポインタの要素型
     * @param r ムーブ元ポインタ
     * @return このポインタ
     */
    template<typename Y>
    nonnull_ptr &operator=(nonnull_ptr<Y> &&r) noexcept {
        m_sp = std::move(r.shared());
        return *this;
    }

    /// 参照カウントを取得します
    [[nodiscard]] long use_count() const noexcept {
        return m_sp.use_count();
    }

    /// shared_ptrを取得します
    [[nodiscard]] std::shared_ptr<T> shared() const noexcept {
        return m_sp;
    }

    /// 間接参照演算子
    [[nodiscard]] T &operator*() const noexcept {
        assert(m_sp != nullptr);
        return *m_sp;
    }

    /// 生ポインタを取得します
    T *get() const noexcept {
        return m_sp.get();
    }

    /// メンバーアクセス演算子
    T *operator->() const noexcept {
        return m_sp.get();
    }

private:
    /**
     * shared_ptrから構築します(内部用)
     * @tparam Y 構築元共有ポインタの要素型
     * @param r 構築元共有ポインタ
     */
    template<typename Y>
    explicit nonnull_ptr(const std::shared_ptr<Y> &r) noexcept
        : m_sp(r) {
        assert(m_sp != nullptr);
    }

private:
    std::shared_ptr<T> m_sp;
};

/// ==比較演算子
template<typename T, typename U>
bool operator ==(const nonnull_ptr<T> &a, const nonnull_ptr<U> &b) noexcept {
    return a.shared() == b.shared();
}

/// !=比較演算子
template<typename T, typename U>
bool operator !=(const nonnull_ptr<T> &a, const nonnull_ptr<U> &b) noexcept {
    return a.shared() != b.shared();
}

/**
 * 非NULLポインタを作成します
 * @tparam T 要素型
 * @tparam Args 初期化引数
 * @param args 初期化引数
 * @return Tのnonnull_ptr
 */
template <typename T, typename ...Args>
nonnull_ptr<T> make_nonnull(Args&& ...args) {
    return nonnull_ptr<T> { std::make_shared<T>(std::forward<Args>(args)...) };
}
}

#endif //NULL_SAFETY_CPP_NONULL_PTR_H
