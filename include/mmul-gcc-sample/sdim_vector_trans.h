#ifndef MMUL_GCC_SAMPLE_SDIM_VECTOR_TRANS_H_
#define MMUL_GCC_SAMPLE_SDIM_VECTOR_TRANS_H_

#include "mmul-gcc-sample/matrix_mul.h"
#include "mmul-gcc-sample/executable.h"
#include "mmul-gcc-sample/common.h"
#include <vector>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief std::vector の1次元配列で表現された行列の積を計算するためのクラス．
 */
class SDimVectorTrans :
  public MatrixMul,
  public Executable {
public:
  /** デフォルトコンストラクタ */
  SDimVectorTrans();

  /** デストラクタ */
  ~SDimVectorTrans();

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
  /** 行列 */
  std::vector<double> a_;

  /** 行列 */
  std::vector<double> b_;

  /** 行列積を格納するための変数 */
  std::vector<double> c_;
};

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_SDIM_VECTOR_TRANS_H_
