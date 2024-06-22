/**
 * @file executable.h
 * @brief 実行する機能をもつインタフェースクラスを定義するヘッダファイル．
 */

#ifndef MMUL_GCC_SAMPLE_EXECUTABLE_H_
#define MMUL_GCC_SAMPLE_EXECUTABLE_H_

#include <string>

/**
 * @brief 本プログラムが提供する名前空間．
 */
namespace mmul {

/**
 * @brief 実行する機能をもつインタフェースクラス．
 */
class Executable {
public:
  /** デストラクタ */
  virtual ~Executable();

  /**
   * 初期化する．
   */
  virtual void Init() = 0;

  /**
   * 実行する．
   *
   * @return 成功したら true.
   */
  virtual bool Execute() = 0;

  /**
   * 実行する内容を表すタグ．
   *
   * @return タグ．
   */
  virtual std::string Tag() const = 0;
};

} // namespace mmul

#endif // MMUL_GCC_SAMPLE_EXECUTABLE_H_
