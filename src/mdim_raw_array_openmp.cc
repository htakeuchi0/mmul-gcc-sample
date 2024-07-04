#include "mmul-gcc-sample/mdim_raw_array_openmp.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
MDimRawArrayOpenMP::MDimRawArrayOpenMP() {}

/**
 * 初期化する．
 */
void MDimRawArrayOpenMP::Init() {
  util::Fill(a_, 1.0);
  util::Fill(b_, 1.0);
  util::Fill(c_, 0.0);
}

/**
 * 行列積を計算する．
 */
void MDimRawArrayOpenMP::Compute() {
  unsigned int j = 0;
  unsigned int k = 0;
  double cij = 0.0;
  #pragma omp parallel for private(j, k, cij)
  for (unsigned int i = 0; i < const_val::kSize; i++) {
    for (j = 0; j < const_val::kSize; j++) {
      cij = 0.0;
      for (k = 0; k < const_val::kSize; k++) {
        cij += a_[i][k] * b_[k][j];
      }
      c_[i][j] = cij;
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool MDimRawArrayOpenMP::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string MDimRawArrayOpenMP::Tag() const {
  return "mdim_raw_array_openmp";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double MDimRawArrayOpenMP::GetResult(std::size_t i, std::size_t j) const {
  return c_[i][j];
}

} // namespace mmul
