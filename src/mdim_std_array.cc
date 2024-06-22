#include "mmul-gcc-sample/mdim_std_array.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
MDimStdArray::MDimStdArray() {}

/**
 * 初期化する．
 */
void MDimStdArray::Init() {
  util::Fill(a_, 1.0);
  util::Fill(b_, 1.0);
  util::Fill(c_, 0.0);
}

/**
 * 行列積を計算する．
 */
void MDimStdArray::Compute() {
  for (unsigned int i = 0; i < const_val::kSize; i++) {
    for (unsigned int j = 0; j < const_val::kSize; j++) {
      double& cij = c_[i][j];
      for (unsigned int k = 0; k < const_val::kSize; k++) {
        cij += a_[i][k] * b_[k][j];
      }
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool MDimStdArray::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string MDimStdArray::Tag() const {
  return "mdim_std_array";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double MDimStdArray::GetResult(std::size_t i, std::size_t j) const {
  return c_[i][j];
}

} // namespace mmul
