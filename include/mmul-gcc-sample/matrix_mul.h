/**
 * @file matrix_mul.h
 * @brief 行列積を計算するためのクラステンプレートを定義するヘッダファイル．
 */

#ifndef MMUL_GCC_SAMPLE_MATRIX_MUL_H_
#define MMUL_GCC_SAMPLE_MATRIX_MUL_H_

#include <cstddef>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief 行列積を計算するためのクラス．
 */
class MatrixMul {
public:
  /** デストラクタ */
  virtual ~MatrixMul();

  /**
   * 行列積を計算する．
   */
  virtual void Compute() = 0;

  /**
   * 実行結果を返す．
   *
   * @param i 行番号
   * @param j 列番号
   * @return 実行結果．
   */
  virtual double GetResult(std::size_t i, std::size_t j) const = 0;
};

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_MATRIX_MUL_H_
