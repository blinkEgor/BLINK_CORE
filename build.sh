#!/bin/bash
# ----------------------------------------
# build.sh — сборка ядра ECS_CORE под Linux
# Автор: Егор
# ----------------------------------------

# Параметры по умолчанию
BUILD_TYPE="Debug" # Тип сборки ( Debug/Release )
BINARY_NAME="core" # Имя бинарника

ENABLE_SDL="OFF" # Подключить SDL

TARGET_OS="linux" # Сборка под Linux

# Аргументы из командной строки ( если переданы )
if [ ! -z "$1" ]; then
  BUILD_TYPE=$1
fi

if [ ! -z "$2" ]; then
  BINARY_NAME=$2
fi

if [ ! -z "$3" ]; then
  ENABLE_SDL=$3
fi

if [ ! -z "$4" ]; then
  TARGET_OS=$4
fi

# Каталог сборки
BUILD_DIR="build"

# Создание build, если нет
mkdir -p $BUILD_DIR

# Конфигурация сборки
cmake -B $BUILD_DIR \
      -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DBINARY_NAME=$BINARY_NAME \
      -DENABLE_SDL=$ENABLE_SDL \
      -DTARGET_OS=$TARGET_OS

# Сборка
cmake --build $BUILD_DIR

# Финальное сообщение
echo "The binary is ready: bin/$BINARY_NAME"