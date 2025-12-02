#!/bin/bash
echo "Build MyCodeEditor  Qt5..."

# Создаем директорию сборки
rm -rf build
mkdir -p build
cd build

# Config CMake
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build
make -j$(nproc)

echo "Build Complete!"
echo "Binary: ./build/MyCodeEditor"
