#!/bin/bash

MAIN_FILES="main/main.cc"
CXX_FLAGS="--std=c++17"
SRC_FILES="src/executable.cc src/matrix_mul.cc src/mdim_raw_array.cc src/mdim_new_array.cc src/mdim_std_array.cc src/mdim_vector.cc src/sdim_new_array.cc src/sdim_raw_array.cc src/sdim_std_array.cc src/sdim_vector.cc src/sdim_raw_array_trans.cc src/sdim_new_array_trans.cc src/sdim_std_array_trans.cc src/sdim_vector_trans.cc"
INCLUDES="./include"
OPTIMS=("-O0" "-O1" "-O2" "-O3")
for OPTIM in ${OPTIMS[@]}; do
  OUT="mmul${OPTIM}"
  rm ${OUT} 2>/dev/null
done

for OPTIM in ${OPTIMS[@]}; do
  OUT="mmul${OPTIM}"
  g++ ${CXX_FLAGS} ${OPTIM} ${MAIN_FILES} ${SRC_FILES} -I${INCLUDES} -o ${OUT}

  echo "Run ${OUT}"
  ./${OUT} > mmul${OPTIM}.json
  echo -e -n "\n"
done
