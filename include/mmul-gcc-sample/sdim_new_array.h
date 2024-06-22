#ifndef MMUL_GCC_SAMPLE_SDIM_NEW_ARRAY_H_
#define MMUL_GCC_SAMPLE_SDIM_NEW_ARRAY_H_

#include "mmul-gcc-sample/matrix_mul.h"
#include "mmul-gcc-sample/executable.h"
#include "mmul-gcc-sample/common.h"
#include <array>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief new で確保した1次元配列で表現された行列の積を計算するためのクラス．
 */
class SDimNewArray :
  public MatrixMul,
  public Executable {
public:
  /** デフォルトコンストラクタ． */
  SDimNewArray();

  /** デストラクタ． */
  ~SDimNewArray();

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
   * @param i 行番号
   * @param j 列番号
   * @return 実行結果．
   */
  double GetResult(std::size_t i, std::size_t j) const override;

private:
  /**
   * 新しい行列をヒープ領域に生成して返す．
   *
   * @param[in] m 列数
   * @param[in] n 行数
   * @return 行列の(1, 1)成分へのポインタ
   */
  static double* NewMatrix(std::size_t m, std::size_t n);

  /**
   * ヒープ領域に生成した行列を削除する．
   *
   * @param[in,out] arr 行列
   */
  static void DeleteMatrix(double*& arr);

private:
  /** 行列 */
  double* a_;

  /** 行列 */
  double* b_;

  /** 行列積を格納するための変数 */
  double* c_;
};

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_SINGLE_DIMENTiONAL_MAtRIX_MUL_
