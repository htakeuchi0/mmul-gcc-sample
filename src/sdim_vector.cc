#include "mmul-gcc-sample/sdim_vector.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
SDimVector::SDimVector() :
  a_(const_val::kSize * const_val::kSize), 
  b_(const_val::kSize * const_val::kSize), 
  c_(const_val::kSize * const_val::kSize) {}

/** デストラクタ */
SDimVector::~SDimVector() {
}

/**
 * 初期化する．
 */
void SDimVector::Init() {
  std::fill(a_.begin(), a_.end(), 1.0);
  std::fill(b_.begin(), b_.end(), 1.0);
  std::fill(c_.begin(), c_.end(), 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimVector::Compute() {
  for (unsigned int i = 0; i < const_val::kSize; i++) {
    for (unsigned int j = 0; j < const_val::kSize; j++) {
      double& cij = c_[i + const_val::kSize*j];
      for (unsigned int k = 0; k < const_val::kSize; k++) {
        cij += a_[i + const_val::kSize*k] * b_[k + const_val::kSize*j];
      }
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool SDimVector::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimVector::Tag() const {
  return "sdim_vector";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double SDimVector::GetResult(std::size_t i, std::size_t j) const {
  return c_[i + const_val::kSize*j];
}

} // namespace mmul
