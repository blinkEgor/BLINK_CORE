#!/bin/bash
# ----------------------------------------
# build.sh — сборка ядра BLINK_CORE под Linux
# Автор: Егор
# ----------------------------------------

# Параметры по умолчанию
BINARY_NAME="core" # Имя бинарника
BUILD_TYPE="Debug" # Тип сборки ( Debug/Release )

TARGET_OS="linux" # Сборка под Linux

ENABLE_BLINK_API="OFF" # Подключить API движка
ENABLE_SDL2="OFF" # Подключить SDL

# Аргументы из командной строки ( если переданы )
if [ ! -z "$1" ]; then
  BINARY_NAME=$1
fi
if [ ! -z "$2" ]; then
  BUILD_TYPE=$2
fi
if [ ! -z "$3" ]; then
  TARGET_OS=$3
fi
if [ ! -z "$4" ]; then
  ENABLE_BLINK_API=$4
fi
if [ ! -z "$5" ]; then
  ENABLE_SDL2=$5
fi

# Каталог сборки
BUILD_DIR="build"

# Создание build, если нет
mkdir -p $BUILD_DIR

# Конфигурация сборки
if ! cmake -B $BUILD_DIR \
      -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DBINARY_NAME=$BINARY_NAME \
      -DTARGET_OS=$TARGET_OS \
      -DENABLE_BLINK_API=$ENABLE_BLINK_API \
      -DENABLE_SDL2=$ENABLE_SDL2; then
    echo "Error config CMake!"
    exit 1
fi

# Сборка
if ! cmake --build $BUILD_DIR; then
    echo "Build failed!"
    exit 1
fi

# Проверка бинарника
if [ -f "bin/$BINARY_NAME" ]; then
    echo "The binary is ready: bin/$BINARY_NAME"
else
    echo "Binary not found in bin/$BINARY_NAME!"
    exit 1
fi