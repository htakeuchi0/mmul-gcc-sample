#!/bin/bash

#
# AVXパターンで計測するためのスクリプト．
#

MAIN_FILES="main/main.cc"
CXX_FLAGS="--std=c++17"
SRC_FILES="src/executable.cc src/matrix_mul.cc src/mdim_raw_array.cc src/mdim_new_array.cc src/mdim_std_array.cc src/mdim_vector.cc src/sdim_new_array.cc src/sdim_raw_array.cc src/sdim_std_array.cc src/sdim_vector.cc src/sdim_raw_array_trans.cc src/sdim_new_array_trans.cc src/sdim_std_array_trans.cc src/sdim_vector_trans.cc src/mdim_raw_array_openmp.cc src/sdim_vector_trans_openmp.cc src/sdim_std_array_avx.cc src/sdim_raw_array_avx.cc src/sdim_std_array_avx_unroll.cc src/sdim_raw_array_avx_unroll.cc"
INCLUDES="./include"
OPTIMS=("-O0" "-O1" "-O2" "-O3")
for OPTIM in ${OPTIMS[@]}; do
  OUT="mmul${OPTIM}"
  rm ${OUT} 2>/dev/null
done

for OPTIM in ${OPTIMS[@]}; do
  OUT="mmul${OPTIM}"
  g++ ${CXX_FLAGS} ${OPTIM} ${MAIN_FILES} ${SRC_FILES} -march=native -mavx2 -I${INCLUDES} -o ${OUT}

  echo "Run ${OUT}"
  mkdir -p log >/dev/null 2>&1
  ./${OUT} avx | tee log/mmul${OPTIM}-avx.json
  echo -e -n "\n"
done
