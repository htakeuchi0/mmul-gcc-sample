#include "mmul-gcc-sample/sdim_new_array.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ． */
SDimNewArray::SDimNewArray() {
  a_ = nullptr;
  b_ = nullptr;
  c_ = nullptr;
}

/** デストラクタ． */
SDimNewArray::~SDimNewArray() {
  DeleteMatrix(a_);
  DeleteMatrix(b_);
  DeleteMatrix(c_);
}

/**
 * 初期化する．
 */
void SDimNewArray::Init() {
  a_ = NewMatrix(const_val::kSize, const_val::kSize);
  b_ = NewMatrix(const_val::kSize, const_val::kSize);
  c_ = NewMatrix(const_val::kSize, const_val::kSize);

  auto num_entries = const_val::kSize * const_val::kSize;
  std::fill(a_, a_ + num_entries, 1.0);
  std::fill(b_, b_ + num_entries, 1.0);
  std::fill(c_, c_ + num_entries, 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimNewArray::Compute() {
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
bool SDimNewArray::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimNewArray::Tag() const {
  return "sdim_new_array";
}

/**
 * 実行結果を返す．
 *
 * @param i 行番号
 * @param j 列番号
 * @return 実行結果．
 */
double SDimNewArray::GetResult(std::size_t i, std::size_t j) const {
  return c_[i + const_val::kSize*j];
}

/**
 * 新しい行列をヒープ領域に生成して返す．
 *
 * @param[in] m 列数
 * @param[in] n 行数
 * @return 行列の(1, 1)成分へのポインタ
 */
double* SDimNewArray::NewMatrix(std::size_t m, std::size_t n) {
  double *arr = new double[m * n];
  return arr;
}

/**
 * ヒープ領域に生成した行列を削除する．
 *
 * @param[in,out] arr 行列
 */
void SDimNewArray::DeleteMatrix(double*& arr) {
  delete [] arr;
  arr = nullptr;
}

} // namespace mmul
