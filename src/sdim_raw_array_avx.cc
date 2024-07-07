#ifdef __AVX2__

#include "mmul-gcc-sample/sdim_raw_array_avx.h"
#include "mmul-gcc-sample/common.h"
#include <immintrin.h>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
SDimRawArrayAVX::SDimRawArrayAVX() {}

/**
 * 初期化する．
 */
void SDimRawArrayAVX::Init() {
  util::Fill(a_, 1.0);
  util::Fill(b_, 1.0);
  util::Fill(c_, 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimRawArrayAVX::Compute() {
  constexpr std::size_t kSkipNumIndices = 256 / 64;
  for (unsigned int i = 0; i < const_val::kSize; i += kSkipNumIndices) {
    for (unsigned int j = 0; j < const_val::kSize; j++) {
      __m256d added = _mm256_load_pd(&c_[i + const_val::kSize*j]);
      for (unsigned int k = 0; k < const_val::kSize; k++) {
        __m256d broadcast_b = _mm256_broadcast_sd(&b_[k + const_val::kSize*j]);
        __m256d loaded_a = _mm256_load_pd(&a_[i + const_val::kSize*k]);
        __m256d multiplied = _mm256_mul_pd(loaded_a, broadcast_b);
        added = _mm256_add_pd(added, multiplied);
      }
      _mm256_store_pd(&c_[i + const_val::kSize*j], added);
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool SDimRawArrayAVX::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimRawArrayAVX::Tag() const {
  return "sdim_raw_array_avx";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double SDimRawArrayAVX::GetResult(std::size_t i, std::size_t j) const {
  return c_[i + const_val::kSize*j];
}

} // namespace mmul

#endif // ifdef __AVX2__
