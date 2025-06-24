#!/bin/bash
# ----------------------------------------
# build.sh — сборка ядра ECS_CORE под Linux
# Автор: Егор
# ----------------------------------------

# Параметры по умолчанию
BUILD_TYPE="Debug"
BINARY_NAME="core"

# Аргументы из командной строки ( если переданы )
if [ ! -z "$1" ]; then
  BUILD_TYPE=$1  # Первый аргумент — тип сборки ( Debug/Release )
fi

if [ ! -z "$2" ]; then
  BINARY_NAME=$2  # Второй аргумент — имя бинарника
fi

# Каталог сборки
BUILD_DIR="build"

# Создание build, если нет
mkdir -p $BUILD_DIR

# Конфигурация сборки
cmake -B $BUILD_DIR -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBINARY_NAME=$BINARY_NAME

# Сборка
cmake --build $BUILD_DIR

# Финальное сообщение
echo "The binary is ready: $BUILD_DIR/bin/$BINARY_NAME"