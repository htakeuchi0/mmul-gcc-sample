/**
 * @file common.h
 * @brief 共通事項を定義するヘッダファイル．
 */

#ifndef MMUL_GCC_SAMPLE_COMMON_H_
#define MMUL_GCC_SAMPLE_COMMON_H_

#include <algorithm>
#include <cstddef>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief 定数を定義する名前空間．
 */
namespace const_val {

/**
 * 行列サイズ．
 */
constexpr std::size_t kSize = 256;

} // namespace const_val

/**
 * @brief ユーティリティ関数をまとめた名前空間．
 */
namespace util {
  /**
   * すべての要素を同じ値で埋める．
   *
   * @tparam T 配列の要素の型
   * @tparam M 行数
   * @tparam N 列数
   * @param[in,out] arr 2次元配列
   * @param[in] value 値
   */
  template <typename T, std::size_t M, std::size_t N>
  void Fill(T (&arr)[M][N], const T& value) {
    for (unsigned int i = 0; i < M; i++) {
      std::fill(std::begin(arr[i]), std::end(arr[i]), value);
    }
  }

  /**
   * すべての要素を同じ値で埋める．
   *
   * @tparam T 配列の要素の型
   * @tparam N 配列の要素数
   * @param[in,out] arr 2次元配列
   * @param[in] value 値
   */
  template <typename T, std::size_t N>
  void Fill(T (&arr)[N], const T& value) {
    std::fill(std::begin(arr), std::end(arr), value);
  }

  /**
   * すべての要素を同じ値で埋める．
   *
   * @tparam T 配列の要素の型
   * @tparam M 行数
   * @tparam N 列数
   * @param[in,out] arr 2次元配列
   * @param[in] value 値
   */
  template <typename T, std::size_t M, std::size_t N>
  void Fill(std::array<std::array<double, N>, M>& arr, const T& value) {
    for (unsigned int i = 0; i < M; i++) {
      std::fill(arr[i].begin(), arr[i].end(), value);
    }
  }

  /**
   * すべての要素を同じ値で埋める．
   *
   * @tparam T 配列の要素の型
   * @param[in,out] arr 2次元配列
   * @param[in] m 行数
   * @param[in] n 列数
   * @param[in] value 値
   */
  template <typename T>
  void Fill(T **arr, std::size_t m, std::size_t n, const T& value) {
    for (unsigned int i = 0; i < m; i++) {
      std::fill(arr[i], arr[i] + n, value);
    }
  }

  /**
   * すべての要素を同じ値で埋める．
   *
   * @tparam T 配列の要素の型
   * @param[in,out] arr 2次元配列
   * @param[in] value 値
   */
  template <typename T>
  void Fill(std::vector<std::vector<T>>& arr, const T& value) {
    for (unsigned int i = 0, n = arr.size(); i < n; i++) {
      std::fill(arr[i].begin(), arr[i].end(), value);
    }
  }

  /**
   * 転置行列を返す．
   *
   * @tparam T 行列の要素の型
   * @tparam N 列数
   * @param[in] arr もとの行列
   * @param[out] trans 転置行列
   */
  template <typename T, std::size_t N>
  void Transpose(const T (&arr)[N * N], T (&trans)[N * N]) {
    for (unsigned int i = 0; i < N; i++) {
      for (unsigned int j = 0; j < N; j++) {
        trans[j + const_val::kSize*i] = arr[i + const_val::kSize*j];
      }
    }
  }

  /**
   * 転置行列を返す．
   *
   * @tparam T 行列の要素の型
   * @tparam N 列数
   * @param[in] arr もとの行列
   * @param[out] trans 転置行列
   */
  template <typename T, std::size_t N>
  void Transpose(const std::array<T, N * N>& arr, std::array<T, N * N>& trans) {
    for (unsigned int i = 0; i < N; i++) {
      for (unsigned int j = 0; j < N; j++) {
        trans[j + N*i] = arr[i + N*j];
      }
    }
  }

  /**
   * 転置行列を返す．
   *
   * @tparam T 行列の要素の型
   * @param[in] arr もとの行列
   * @param[out] trans 転置行列
   * @param[in] n 列数
   */
  template <typename T>
  void Transpose(const T *const arr, T *const trans, std::size_t n) {
    for (unsigned int i = 0; i < n; i++) {
      for (unsigned int j = 0; j < n; j++) {
        trans[j + n*i] = arr[i + n*j];
      }
    }
  }

  /**
   * 転置行列を返す．
   *
   * @tparam T 行列の要素の型
   * @param[in] arr もとの行列
   * @param[out] trans 転置行列
   * @param[in] n 列数
   */
  template <typename T>
  void Transpose(const std::vector<T>& arr, std::vector<T>& trans, std::size_t n) {
    for (unsigned int i = 0; i < n; i++) {
      for (unsigned int j = 0; j < n; j++) {
        trans[j + n*i] = arr[i + n*j];
      }
    }
  }

  /**
   * 転置行列を返す．
   *
   * @tparam T 行列の要素の型
   * @param[in] arr もとの行列
   * @param[out] trans 転置行列
   * @param[in] n 列数
   */
  template <typename T>
  void TransposeOpenMP(const std::vector<T>& arr, std::vector<T>& trans, std::size_t n) {
    unsigned int j = 0;
    #pragma omp parallel for private(j)
    for (unsigned int i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        trans[j + n*i] = arr[i + n*j];
      }
    }
  }
} // namespace util

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_COMMON_H_
