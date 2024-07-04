#include "mmul-gcc-sample/sdim_std_array_avx_unroll.h"
#include "mmul-gcc-sample/common.h"
#include <immintrin.h>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/** デフォルトコンストラクタ */
SDimStdArrayAVXUnroll::SDimStdArrayAVXUnroll() {}

/**
 * 初期化する．
 */
void SDimStdArrayAVXUnroll::Init() {
  std::fill(a_.begin(), a_.end(), 1.0);
  std::fill(b_.begin(), b_.end(), 1.0);
  std::fill(c_.begin(), c_.end(), 0.0);
}

/**
 * 行列積を計算する．
 */
void SDimStdArrayAVXUnroll::Compute() {
  constexpr std::size_t kSkipNumIndices = 256 / 64;
  constexpr std::size_t kUnroll = 4;
  for (unsigned int i = 0; i < const_val::kSize; i += kSkipNumIndices*kUnroll) {
    for (unsigned int j = 0; j < const_val::kSize; j++) {
      __m256d added0 = _mm256_load_pd(&c_[i + const_val::kSize*j]);
      __m256d added1 = _mm256_load_pd(&c_[i + kSkipNumIndices + const_val::kSize*j]);
      __m256d added2 = _mm256_load_pd(&c_[i + kSkipNumIndices*2 + const_val::kSize*j]);
      __m256d added3 = _mm256_load_pd(&c_[i + kSkipNumIndices*3 + const_val::kSize*j]);

      for (unsigned int k = 0; k < const_val::kSize; k++) {
        __m256d broadcast_b = _mm256_broadcast_sd(&b_[k + const_val::kSize*j]);

        __m256d loaded_a = _mm256_load_pd(&a_[i + const_val::kSize*k]);
        __m256d multiplied = _mm256_mul_pd(loaded_a, broadcast_b);
        added0 = _mm256_add_pd(added0, multiplied);

        loaded_a = _mm256_load_pd(&a_[i + kSkipNumIndices + const_val::kSize*k]);
        multiplied = _mm256_mul_pd(loaded_a, broadcast_b);
        added1 = _mm256_add_pd(added1, multiplied);

        loaded_a = _mm256_load_pd(&a_[i + kSkipNumIndices*2 + const_val::kSize*k]);
        multiplied = _mm256_mul_pd(loaded_a, broadcast_b);
        added2 = _mm256_add_pd(added2, multiplied);

        loaded_a = _mm256_load_pd(&a_[i + kSkipNumIndices*3 + const_val::kSize*k]);
        multiplied = _mm256_mul_pd(loaded_a, broadcast_b);
        added3 = _mm256_add_pd(added3, multiplied);
      }

      _mm256_store_pd(&c_[i + const_val::kSize*j], added0);
      _mm256_store_pd(&c_[i + kSkipNumIndices + const_val::kSize*j], added1);
      _mm256_store_pd(&c_[i + kSkipNumIndices*2 + const_val::kSize*j], added2);
      _mm256_store_pd(&c_[i + kSkipNumIndices*3 + const_val::kSize*j], added3);
    }
  }
}

/**
 * 実行する．
 *
 * @return 成功したときはtrueを返す．
 */
bool SDimStdArrayAVXUnroll::Execute() {
  Compute();
  return true;
}

/**
 * 実行した内容を表すタグを返す．
 *
 * @return タグ名
 */
std::string SDimStdArrayAVXUnroll::Tag() const {
  return "sdim_std_array_avx_unroll";
}

/**
 * 実行結果を返す．
 *
 * @param[in] i 行番号
 * @param[in] j 列番号
 * @return 実行結果．
 */
double SDimStdArrayAVXUnroll::GetResult(std::size_t i, std::size_t j) const {
  return c_[i * const_val::kSize*j];
}

} // namespace mmul
