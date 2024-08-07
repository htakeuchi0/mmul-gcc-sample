#ifndef MMUL_GCC_SAMPLE_SDIM_RAW_ARRAY_AVX_H_
#define MMUL_GCC_SAMPLE_SDIM_RAW_ARRAY_AVX_H_

#ifdef __AVX2__

#include "mmul-gcc-sample/common.h"
#include "mmul-gcc-sample/matrix_mul.h"
#include "mmul-gcc-sample/executable.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief 生の1次元配列で表現された行列の積を計算するためのクラス．
 */
class SDimRawArrayAVX :
  public MatrixMul,
  public Executable {
public:
  /** デフォルトコンストラクタ */
  SDimRawArrayAVX();

  /**
   * 初期化する．
   */
  void Init() override;

  /**
   * 行列積を計算する．
   */
  void Compute() override;

  /**
   * 実行する．
   *
   * @return 成功したときはtrueを返す．
   */
  bool Execute() override;

  /**
   * 実行した内容を表すタグを返す．
   *
   * @return タグ名
   */
  std::string Tag() const override;

  /**
   * 実行結果を返す．
   *
   * @param[in] i 行番号
   * @param[in] j 列番号
   * @return 実行結果．
   */
  double GetResult(std::size_t i, std::size_t j) const override;

private:
  /**
   * 行列積をとるための行列．
   */
  alignas(32) double a_[const_val::kSize * const_val::kSize];

  /**
   * 行列積をとるための行列．
   */
  alignas(32) double b_[const_val::kSize * const_val::kSize];

  /**
   * 行列積の結果を格納する行列．
   */
  alignas(32) double c_[const_val::kSize * const_val::kSize];
};

} // namespace mmul

#endif // ifdef __AVX2__

#endif // MMUL_GCC_SAMPLE_SDIM_RAW_ARRAY_AVX_H_
