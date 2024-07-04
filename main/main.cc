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
#include "mmul-gcc-sample/mdim_raw_array_openmp.h"
#include "mmul-gcc-sample/sdim_vector_trans_openmp.h"
#include <chrono>
#include <map>
#include <iomanip>
#include <iostream>
#include <string>
#include <memory>

/**
 * 行列積計算ロジックを返す．
 *
 * @param[in] label ロジックのラベル
 * @return 行列積計算ロジック
 */
std::unique_ptr<mmul::Executable> MatrixMul(const std::string& label) {
  if (label == "mdim_raw_array") {
    return std::make_unique<mmul::MDimRawArray>();
  }

  if (label == "mdim_std_array") {
    return std::make_unique<mmul::MDimStdArray>();
  }

  if (label == "mdim_new_array") {
    return std::make_unique<mmul::MDimNewArray>();
  }

  if (label == "mdim_vector") {
    return std::make_unique<mmul::MDimVector>();
  }

  if (label == "sdim_raw_array") {
    return std::make_unique<mmul::MDimRawArray>();
  }

  if (label == "sdim_std_array") {
    return std::make_unique<mmul::SDimStdArray>();
  }

  if (label == "sdim_new_array") {
    return std::make_unique<mmul::SDimNewArray>();
  }

  if (label == "sdim_vector") {
    return std::make_unique<mmul::SDimVector>();
  }

  if (label == "sdim_raw_array_trans") {
    return std::make_unique<mmul::SDimRawArrayTrans>();
  }

  if (label == "sdim_std_array_trans") {
    return std::make_unique<mmul::SDimStdArrayTrans>();
  }

  if (label == "sdim_new_array_trans") {
    return std::make_unique<mmul::SDimNewArrayTrans>();
  }

  if (label == "sdim_vector_trans") {
    return std::make_unique<mmul::SDimVectorTrans>();
  }

  if (label == "mdim_raw_array_openmp") {
    return std::make_unique<mmul::MDimRawArrayOpenMP>();
  }

  if (label == "sdim_vector_trans_openmp") {
    return std::make_unique<mmul::SDimVectorTransOpenMP>();
  }

  return std::unique_ptr<mmul::Executable>();
}

/**
 * 実行時間を計測して返す．
 *
 * @param[in] executable 実行ロジック
 * @param[in] num_samples 実行時間のサンプル数
 * @param[in] num_loops 実行時間を計測するために何回連続実行するか
 * @return 実行時間 [sec] のリスト
 */
std::vector<double> EvaluatePerformance(
    std::unique_ptr<mmul::Executable>& executable,
    int num_samples,
    int num_loops) {
  if (executable == nullptr) {
    return std::vector<double>();
  }

  std::vector<double> elapsed_times(num_samples);
  
  executable->Init();
  for (int i = 0; i < num_samples; i++) {
    auto begin = std::chrono::system_clock::now();
    for (int j = 0; j < num_loops; j++) {
      executable->Execute();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - begin;
    auto elapsed_sec = static_cast<double>(
        std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()) / 1.0e+6;
    elapsed_sec /= num_loops;
    elapsed_times[i] = elapsed_sec;
  }

  return elapsed_times;
}

/**
 * 結果をJSON形式で出力する．
 *
 * @param[in] result 実行結果
 * @param[in] out 出力先
 * @return 出力ストリームへの参照
 */
std::ostream& PrintResult(
    const std::map<std::string, std::vector<double>>& result,
    std::ostream& out = std::cout) {
  int num_result_data = static_cast<int>(result.size());
  int idx = 0;
  out << "[" << std::endl;
  out << "  {" << std::endl;
  for (const auto& [tag, elapsed_times] : result) {
    out << "    " << std::quoted(tag) << ": [" << std::endl;
    int num_samples = static_cast<int>(elapsed_times.size());
    for (int i = 0; i < num_samples; i++) {
      double elapsed_sec = elapsed_times[i];
      out << "      " << elapsed_sec << std::flush;
      if (i < num_samples - 1) {
        out << "," << std::flush;
      }
      out << std::endl;
    }
    out << "    ]" << std::flush;
    if (idx < num_result_data - 1) {
      out << "," << std::flush;
    }
    out << std::endl;
    idx++;
  }
  out << "  }" << std::endl;
  out << "]" << std::endl;
  return out;
}

int BasicExperiment() {
  std::vector<std::string> labels = {
    "mdim_raw_array",
    "mdim_std_array",
    "mdim_new_array",
    "mdim_vector",
    "sdim_raw_array",
    "sdim_std_array",
    "sdim_new_array",
    "sdim_vector",
    "sdim_raw_array_trans",
    "sdim_std_array_trans",
    "sdim_new_array_trans",
    "sdim_vector_trans"
  };

  int num_samples = 100;
  int num_loops = 10;

  std::map<std::string, std::vector<double>> result;
  for (const auto& label : labels) {
    auto matrix_mul = MatrixMul(label);
    if (!matrix_mul) {
      return 1;
    }

    auto elapsed_times = EvaluatePerformance(matrix_mul, num_samples, num_loops);
    if (elapsed_times.size() == 0) {
      return 1;
    }

    result.emplace(label, elapsed_times);
  }

  PrintResult(result);
  return 0;
}

int OpenMPExperiment() {
  std::vector<std::string> labels = {
    "mdim_raw_array",
    "mdim_raw_array_openmp",
    "sdim_vector_trans",
    "sdim_vector_trans_openmp"
  };

  int num_samples = 100;
  int num_loops = 10;

  std::map<std::string, std::vector<double>> result;
  for (const auto& label : labels) {
    auto matrix_mul = MatrixMul(label);
    if (!matrix_mul) {
      return 1;
    }

    auto elapsed_times = EvaluatePerformance(matrix_mul, num_samples, num_loops);
    if (elapsed_times.size() == 0) {
      return 1;
    }

    result.emplace(label, elapsed_times);
  }

  PrintResult(result);
  return 0;
}

/**
 * 実行用メイン関数．
 *
 * @return 終了コード
 */
int main() {
  int ret_code = OpenMPExperiment();
  return ret_code;
}
