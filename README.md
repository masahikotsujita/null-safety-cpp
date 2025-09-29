# null-safety-cpp

## 概要

C++でのNULL安全モドキのお試し実装です。

## 説明

- `shared_ptr`版
    - `nullable_ptr<T>`はNULL許容の`shared_ptr`です。
        - 後述の`nsf::nonnull_ptr<T>`に変換しないとリソースにアクセスできません。
        - `nsf::nonnull_ptr<T>`に変換するには、以下の方法を使用します：
            - `if_nonnull()`関数で非NULLの場合の処理を記述する。
            - `nonnull_force()`関数で強制的に変換する。NULLだった場合未定義動作となり安全ではありません。
        - 実装の都合上`shared()`関数で中身の`std::shared_ptr<T>`を取れてしまうため`.shared()->`とやるとNULLチェックを迂回してメンバーアクセスできてしまいますが、しないでください。
    - `nonnull_ptr<T>`は非NULL`shared_ptr`です。
        - デフォルト構築できません。
        - `nullptr`から構築できません。
        - 中身がNULLになり得るほとんどのポインタから直接的に構築できません。
        - `make_nonnull<T>`、`nullable_ptr<T>`の`if_nonnull`や`nonnull_force`を通してのみ構築できます。
        - 通常のポインタやスマートポインタ同様`*`や`->`を使ってメンバーにアクセスできます。
    - (未実装)`implicit_nullable_ptr<T>`
        - 暗黙的にアンラップされるNULL許容`shared_ptr`です。
        - 
        - 安全ではありません。極力使用しないでください。

- `unique_ptr`版は未実装です。実装するかは未定です。
- 生ポインタ版は未実装です。実装するかは未定です。
- `optional`版は未実装です。実装するかは未定です。
