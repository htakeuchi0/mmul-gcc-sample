#include "mmul-gcc-sample/sdim_vector_trans.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
SDimVectorTrans::SDimVectorTrans() :
  a_(const_val::kSize * const_val::kSize), 
  b_(const_val::kSize * const_val::kSize), 
  c_(const_val::kSize * const_val::kSize) {}

/** デストラクタ */
SDimVectorTrans::~SDimVectorTrans() {
}

/**
 * 初期化する．
 */
void SDimVectorTrans::Init() {
  std::fill(a_.begin(), a_.end(), 1.0);
  std::fill(b_.begin(), b_.end(), 1.0);
  std::fill(c_.begin(), c_.end(), 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimVectorTrans::Compute() {
  std::vector<double> trans_a(const_val::kSize * const_val::kSize);
  util::Transpose(a_, trans_a, const_val::kSize);
  for (unsigned int i = 0; i < const_val::kSize; i++) {
    for (unsigned int j = 0; j < const_val::kSize; j++) {
      double& cij = c_[i + const_val::kSize*j];
      for (unsigned int k = 0; k < const_val::kSize; k++) {
        cij += trans_a[const_val::kSize*i + k] * b_[k + const_val::kSize*j];
      }
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool SDimVectorTrans::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimVectorTrans::Tag() const {
  return "sdim_vector_trans";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double SDimVectorTrans::GetResult(std::size_t i, std::size_t j) const {
  return c_[i + const_val::kSize*j];
}

} // namespace mmul
