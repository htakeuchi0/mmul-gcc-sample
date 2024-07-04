#include "mmul-gcc-sample/sdim_vector_trans_openmp.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
SDimVectorTransOpenMP::SDimVectorTransOpenMP() :
  a_(const_val::kSize * const_val::kSize), 
  b_(const_val::kSize * const_val::kSize), 
  c_(const_val::kSize * const_val::kSize) {}

/** デストラクタ */
SDimVectorTransOpenMP::~SDimVectorTransOpenMP() {
}

/**
 * 初期化する．
 */
void SDimVectorTransOpenMP::Init() {
  std::fill(a_.begin(), a_.end(), 1.0);
  std::fill(b_.begin(), b_.end(), 1.0);
  std::fill(c_.begin(), c_.end(), 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimVectorTransOpenMP::Compute() {
  std::vector<double> trans_a(const_val::kSize * const_val::kSize);
  util::TransposeOpenMP(a_, trans_a, const_val::kSize);

  unsigned int j = 0;
  unsigned int k = 0;
  double cij = 0.0;
  #pragma omp parallel for private(j, k, cij)
  for (unsigned int i = 0; i < const_val::kSize; i++) {
    for (j = 0; j < const_val::kSize; j++) {
      cij = 0.0;
      for (k = 0; k < const_val::kSize; k++) {
        cij += trans_a[const_val::kSize*i + k] * b_[k + const_val::kSize*j];
      }
      c_[i + const_val::kSize*j] = cij;
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool SDimVectorTransOpenMP::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimVectorTransOpenMP::Tag() const {
  return "sdim_vector_trans_openmp";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double SDimVectorTransOpenMP::GetResult(std::size_t i, std::size_t j) const {
  return c_[i + const_val::kSize*j];
}

} // namespace mmul
