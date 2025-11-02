//
// Created by masahiko on 2025/09/27.
//

#ifndef NULL_SAFETY_CPP_NULLABLE_PTR_H
#define NULL_SAFETY_CPP_NULLABLE_PTR_H
#include <memory>

namespace nsf {
template<typename T>
class nonnull_ptr;

/**
 * @brief  NULL許容の強参照共有ポインタ。
 * @tparam T 要素型。
 */
template<typename T>
class nullable_ptr final {
public:
    /// 要素型
    using element_type = T;
    /// 非NULLポインタ型
    using nonnull_type = nonnull_ptr<T>;
    /// weakポインタ型
    using weak_type = std::weak_ptr<T>;

    /// デフォルトコンストラクタ
    nullable_ptr() noexcept
        : m_sp(nullptr) {
    }

    /**
     * 生ポインタから構築するコンストラクタ
     * @tparam Y 構築元ポインタの要素型
     * @param r 構築元ポインタ
     */
    template<typename Y>
    explicit nullable_ptr(Y *r)
        : m_sp(r) {
    }

    /**
     * shared_ptrから構築するコンストラクタ
     * @tparam Y 構築元ポインタの要素型
     * @param r 構築元ポインタ
     */
    template<typename Y>
    explicit nullable_ptr(const std::shared_ptr<Y> &r)
        : m_sp(r) {
    }

    /**
     * weak_ptrから構築するコンストラクタ
     * @tparam Y 構築元ポインタの要素型
     * @param r 構築元ポインタ
     */
    template<typename Y>
    explicit nullable_ptr(const std::weak_ptr<Y> &r) noexcept
        : m_sp(r.lock()) {
    }

    /**
     * 非NULLポインタから構築するコンストラクタ
     * @tparam Y 構築元ポインタの要素型
     * @param r 構築元ポインタ
     */
    template<typename Y>
    nullable_ptr(const nonnull_ptr<Y> &r) noexcept
        : m_sp(r.m_sp) {
    }

    /// nullptrから構築するコンストラクタ
    nullable_ptr(std::nullptr_t) noexcept
        : nullable_ptr() {
    }

    /**
     * コピーコンストラクタ
     * @param r コピー元ポインタ
     */
    nullable_ptr(const nullable_ptr &r)
        : m_sp(r.m_sp) {
    }

    /**
     * コピーコンストラクタ
     * @tparam Y Tに変換可能な要素型
     * @param r コピー元ポインタ
     */
    template<typename Y>
    nullable_ptr(const nullable_ptr<Y> &r)
        : m_sp(r.m_sp) {
    }

    /**
     * ムーブコンストラクタ
     */
    nullable_ptr(nullable_ptr &&r) noexcept
        : m_sp(std::move(r)) {
    }

    /**
     * ムーブコンストラクタ
     * @tparam Y Tに変換可能な要素型
     * @param r 別のnullable_ptr
     */
    template<typename Y>
    nullable_ptr(nullable_ptr<Y> &&r) noexcept
        : m_sp(std::move(r)) {
    }

    /**
     * shared_ptrからのコピー代入演算子
     * @tparam Y Tに変換可能な要素型
     * @param r 右辺値
     * @return このnullable_ptr
     */
    template<typename Y>
    nullable_ptr &operator=(const std::shared_ptr<Y> &r) noexcept {
        m_sp = r;
        return *this;
    }

    /**
     * unique_ptrからのコピー代入演算子
     * @tparam Y 代入元ポインタの要素型
     * @tparam D Deleter
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    template<typename Y, typename D>
    nullable_ptr &operator=(std::unique_ptr<Y, D> &&r) noexcept {
        m_sp == std::move(r);
        return *this;
    }

    /**
     * コピー代入演算子
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    nullable_ptr &operator=(const nullable_ptr &r) noexcept {
        m_sp = r.m_sp;
        return *this;
    }

    /**
     * コピー代入演算子
     * @tparam Y 代入元ポインタの要素型
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    template<typename Y>
    nullable_ptr &operator=(const nullable_ptr<Y> &r) noexcept {
        m_sp = r.m_sp;
        return *this;
    }

    /**
     * ムーブ代入演算子
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    nullable_ptr &operator=(nullable_ptr &&r) noexcept {
        m_sp = std::move(r.m_sp);
        return *this;
    }

    /**
     * ムーブ代入演算子
     * @tparam Y 代入元ポインタの要素型
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    template<typename Y>
    nullable_ptr &operator=(nullable_ptr<Y> &&r) noexcept {
        m_sp = std::move(r.m_sp);
        return *this;
    }

    /**
     * nullable_ptrからのコピー代入演算子
     * @tparam Y 代入元ポインタの要素型
     * @param r 右辺値
     * @return 呼び出し元オブジェクト
     */
    template<typename Y>
    nullable_ptr &operator=(const nonnull_ptr<Y> &r) noexcept {
        m_sp = r.shared();
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

    /**
     * NULLチェックを行い、非NULLならnonnull_ptrに変換してハンドラを呼び出します
     * @tparam ThenHandler ハンドラ
     * @param thenHandler ハンドラ
     */
    template<typename ThenHandler>
    bool if_nonnull(
        const ThenHandler &thenHandler) noexcept(std::is_nothrow_invocable_v<ThenHandler, const nonnull_type &>) {
        if (m_sp) {
            nonnull_type tmp(m_sp);
            thenHandler(tmp);
            return true;
        } else {
            return false;
        }
    }

    /**
     * NULLチェックを行い、非NULLならnonnull_ptrに変換してハンドラを呼び出し、NULLなら
     * @tparam ThenHandler ハンドラ
     * @param thenHandler ハンドラ
     * @tparam ElseHandler ハンドラ
     * @param elseHandler ハンドラ
     */
    template<typename ThenHandler, typename ElseHandler>
    bool if_nonnull(const ThenHandler &thenHandler,
                    const ElseHandler &elseHandler) noexcept(
        std::is_nothrow_invocable_v<ThenHandler, const nonnull_type &> && std::is_nothrow_invocable_v<ElseHandler>) {
        if (m_sp) {
            nonnull_type tmp(m_sp);
            thenHandler(tmp);
            return true;
        } else {
            elseHandler();
            return false;
        }
    }

    /**
     * 強制的にnonnull_ptrに変換し返します。
     * @return nonnull_ptr
     */
    [[nodiscard]] nonnull_type nonnull_force() {
        assert(m_sp != nullptr);
        return nonnull_type{m_sp};
    }

    /**
     * boolキャスト演算子
     * @return 非nullならtrue、そうでなければfalse.
     */
    explicit operator bool() const noexcept {
        return m_sp != nullptr;
    }

private:
    std::shared_ptr<T> m_sp;
};

/// ==比較演算子
template<typename T, typename U>
bool operator ==(const nullable_ptr<T> &a, const nullable_ptr<U> &b) noexcept {
    return a.shared() == b.shared();
}

/// ==比較演算子
template<typename T>
bool operator ==(const nullable_ptr<T> &a, std::nullptr_t) noexcept {
    return !a.shared();
}

/// ==比較演算子
template<typename T>
bool operator ==(std::nullptr_t, const nullable_ptr<T> &b) noexcept {
    return !b.shared();
}

/// !=比較演算子
template<typename T, typename U>
bool operator !=(const nullable_ptr<T> &a, const nullable_ptr<U> &b) noexcept {
    return a.shared() != b.shared();
}

/// !=比較演算子
template<typename T>
bool operator !=(const nullable_ptr<T> &a, std::nullptr_t) noexcept {
    return a.shared() != nullptr;
}

/// !=比較演算子
template<typename T>
bool operator !=(std::nullptr_t, const nullable_ptr<T> &b) noexcept {
    return b.shared() != nullptr;
}
}

#endif // NULL_SAFETY_CPP_NULLABLE_PTR_H
