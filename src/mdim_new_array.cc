#include "mmul-gcc-sample/mdim_new_array.h"
#include "mmul-gcc-sample/common.h"

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ． */
MDimNewArray::MDimNewArray() {
  a_ = nullptr;
  b_ = nullptr;
  c_ = nullptr;
}

/** デストラクタ． */
MDimNewArray::~MDimNewArray() {
  DeleteMatrix(const_val::kSize, a_);
  DeleteMatrix(const_val::kSize, b_);
  DeleteMatrix(const_val::kSize, c_);
}

/**
 * 初期化する．
 */
void MDimNewArray::Init() {
  a_ = NewMatrix(const_val::kSize, const_val::kSize);
  b_ = NewMatrix(const_val::kSize, const_val::kSize);
  c_ = NewMatrix(const_val::kSize, const_val::kSize);
  util::Fill(a_, const_val::kSize, const_val::kSize, 1.0);
  util::Fill(b_, const_val::kSize, const_val::kSize, 1.0);
  util::Fill(c_, const_val::kSize, const_val::kSize, 0.0);
}

/**
 * 行列積を計算する．
 */
void MDimNewArray::Compute() {
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
bool MDimNewArray::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string MDimNewArray::Tag() const {
  return "mdim_new_array";
}

/**
 * 実行結果を返す．
 *
 * @param i 行番号
 * @param j 列番号
 * @return 実行結果．
 */
double MDimNewArray::GetResult(std::size_t i, std::size_t j) const {
  return c_[i][j];
}

/**
 * 新しい行列をヒープ領域に生成して返す．
 *
 * @param[in] m 列数
 * @param[in] n 行数
 * @return 行列の(1, 1)成分へのポインタ
 */
double** MDimNewArray::NewMatrix(std::size_t m, std::size_t n) {
  double **arr = new double*[m];
  for (unsigned int i = 0; i < m; i++) {
    arr[i] = new double[n];
  }
  return arr;
}

/**
 * ヒープ領域に生成した行列を削除する．
 *
 * @param[in] m 列数
 * @param[in,out] arr 行列
 */
void MDimNewArray::DeleteMatrix(std::size_t m, double**& arr) {
  if (arr == nullptr) {
    return;
  }

  for (unsigned int i = 0; i < m; i++) {
    delete [] arr[i];
    arr[i] = nullptr;
  }
  delete [] arr;
  arr = nullptr;
}

} // namespace mmul
