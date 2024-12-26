#!/bin/bash

export CFLAGS="-m32"
export CXXFLAGS="-m32"

BUILD_DIR="build32"

if [ -d "$BUILD_DIR" ]; then
  echo "$BUILD_DIR exists."
else
  echo "$BUILD_DIR does not exist. Creating it"
  mkdir "$BUILD_DIR"
fi

if [ -z "$(ls -A $BUILD_DIR)" ]; then
  echo "$BUILD_DIR is empty, configuring build..."

  cd "$BUILD_DIR" || exit
  cmake -DBUILD_STANDALONE=ON ..
  make
else
  echo "$BUILD_DIR is not empty, running make..."

  cd "$BUILD_DIR" || exit
  make
fi
