#include "mmul-gcc-sample/mdim_raw_array.h"
#include "mmul-gcc-sample/mdim_std_array.h"
#include "mmul-gcc-sample/mdim_new_array.h"
#include "mmul-gcc-sample/mdim_vector.h"
#include "mmul-gcc-sample/sdim_raw_array.h"
#include "mmul-gcc-sample/sdim_std_array.h"
#include "mmul-gcc-sample/sdim_new_array.h"
#include "mmul-gcc-sample/sdim_vector.h"
#include "mmul-gcc-sample/sdim_raw_array_trans.h"
#include "mmul-gcc-sample/sdim_std_array_trans.h"
#include "mmul-gcc-sample/sdim_new_array_trans.h"
#include "mmul-gcc-sample/sdim_vector_trans.h"
#include <iostream>
#include <chrono>

int main() {
  mmul::MDimRawArray mdim_raw_array;
  mmul::MDimStdArray mdim_std_array;
  mmul::MDimNewArray mdim_new_array;
  mmul::MDimVector mdim_vector;
  mmul::SDimRawArray sdim_raw_array;
  mmul::SDimStdArray sdim_std_array;
  mmul::SDimNewArray sdim_new_array;
  mmul::SDimVector sdim_vector;
  mmul::SDimRawArrayTrans sdim_raw_array_trans;
  mmul::SDimStdArrayTrans sdim_std_array_trans;
  mmul::SDimNewArrayTrans sdim_new_array_trans;
  mmul::SDimVectorTrans sdim_vector_trans;

  std::vector<std::reference_wrapper<mmul::Executable>> matrix_muls = {
    mdim_raw_array,
    mdim_std_array,
    mdim_new_array,
    mdim_vector,
    sdim_raw_array,
    sdim_std_array,
    sdim_new_array,
    sdim_vector,
    sdim_raw_array_trans,
    sdim_std_array_trans,
    sdim_new_array_trans,
    sdim_vector_trans,
  };

  int num_loops = 100;
  for (auto& matrix_mul_wrapper : matrix_muls) {
    auto& matrix_mul = matrix_mul_wrapper.get();
    matrix_mul.Init();
    auto begin = std::chrono::system_clock::now();
    for (int i = 0; i < num_loops; i++) {
      matrix_mul.Execute();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - begin;
    auto elapsed_sec = static_cast<double>(
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()) / 1.0e+6;
    elapsed_sec /= num_loops;
    std::cout << matrix_mul.Tag() << ": " << elapsed_sec << "\n";
  }
}
