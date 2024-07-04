#ifndef MMUL_GCC_SAMPLE_SDIM_STD_ARRAY_AVX_H_
#define MMUL_GCC_SAMPLE_SDIM_STD_ARRAY_AVX_H_

#include "mmul-gcc-sample/matrix_mul.h"
#include "mmul-gcc-sample/executable.h"
#include "mmul-gcc-sample/common.h"
#include <array>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @briefl std::arrayの1次元配列で表現された行列の積を計算するためのクラス．
 */
class SDimStdArrayAVX :
  public MatrixMul,
  public Executable {
public:
  /** デフォルトコンストラクタ */
  SDimStdArrayAVX();

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
   * @return 成功したら true.
   */
  bool Execute() override;

  /**
   * 実行する内容を表すタグ．
   *
   * @return タグ．
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
  /** 行列 */
  alignas(32) std::array<double, const_val::kSize * const_val::kSize> a_;

  /** 行列 */
  alignas(32) std::array<double, const_val::kSize * const_val::kSize> b_;

  /** 行列積を格納するための変数 */
  alignas(32) std::array<double, const_val::kSize * const_val::kSize> c_;
};

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_SDIM_STD_ARRAY_AVX_H_
