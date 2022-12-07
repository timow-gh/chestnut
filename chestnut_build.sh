#!/bin/bash

BUILD_DIR=../chestnut_build
SOURCE_DIR=./
INSTALL_DIR=../chestnut_install

mkdir $BUILD_DIR 

cmake -B $BUILD_DIR -S $SOURCE_DIR -G Ninja --preset "unixlike-clang-release" \
-DBUILD_SHARED_LIBS=ON \
-DCMAKE_CXX_STANDARD=20 \
-Dchestnut_TESTS=ON \
-Dchestnut_BENCHMARKS=ON \
-Dchestnut_WARNINGS_AS_ERRORS=ON \
-Dchestnut_PACKAGE=OFF

threads=`nproc`
cmake --build $BUILD_DIR  --config Release --parallel --parallel $threads

mkdir $INSTALL_DIR
cmake --install ./$BUILD_DIR --config Release --prefix $INSTALL_DIR
