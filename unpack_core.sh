#!/bin/bash
# ----------------------------------------------
# unpack_core.sh — распаковка/установка ядра BLINK_CORE и подхвата других компонентов движка
# для использования ядра/движка в продукте
# Автор: blinkEgor
#
# Инструкция:
#	```bash
# 	chmod +x unpack_core.sh	# дать права
# 	./unpack_core.sh	# запустить
# 	```
#
# Далее следовать инструкциям в терменале
# ----------------------------------------------

echo "=== BLINK_CORE Installer ==="

# Запрос целевой директории (относительно домашней)
echo "Введите путь установки в целевую директорию относительно домашней директории (например: myproject или Desktop/myproject): "
read RELATIVE_PATH
TARGET_DIR="$HOME/$RELATIVE_PATH"

mkdir -p "$TARGET_DIR"

# Копирование файлов из текущей директории
echo "Копирование файлов ядра..."
cp -r bin configs include "$TARGET_DIR"/
cp -f LICENSE "$TARGET_DIR"/

# Запрос пути к libblink_api.so (относительно домашней)
echo "Введите путь к директории с blink_api относительно домашней директории: "
read RELATIVE_API_PATH
API_PATH="$HOME/$RELATIVE_API_PATH/bin/libblink_api.so"

if [ -f "$API_PATH" ]; then
	cp "$API_PATH" "$TARGET_DIR/bin/"
	echo "libblink_api.so скопирован"
else
	echo "Внимание: libblink_api.so не найден по пути: $API_PATH! Необходимо установить его отдельно в $TARGET_DIR/bin/."
fi

# Копирование файлов API
echo "Копирование файлов API..."
API_INCLUDE_DIR="$TARGET_DIR/include/blink_api"
mkdir -p "$API_INCLUDE_DIR/abstractions"
mkdir -p "$API_INCLUDE_DIR/stubs"
mkdir -p "$TARGET_DIR/configs/api_plugins"

# Копирование заголовочных файлов
cp -r "$HOME/$RELATIVE_API_PATH/include/blink_api/abstractions"/*.h "$API_INCLUDE_DIR/abstractions/" 2>/dev/null || echo "Не найдены файлы abstractions"
cp -r "$HOME/$RELATIVE_API_PATH/include/blink_api/stubs"/*.h "$API_INCLUDE_DIR/stubs/" 2>/dev/null || echo "Не найдены файлы stubs"
cp "$HOME/$RELATIVE_API_PATH/include/blink_api/api.h" "$API_INCLUDE_DIR/" 2>/dev/null || echo "Не найден api.h"
cp "$HOME/$RELATIVE_API_PATH/include/blink_api/version.h" "$API_INCLUDE_DIR/" 2>/dev/null || echo "Не найден version.h"

# Копирование конфигов
cp "$HOME/$RELATIVE_API_PATH/configs/api_plugins"/*.conf "$TARGET_DIR/configs/api_plugins/" 2>/dev/null || echo "Не найдены конфиги api_plugins"

# Копирование документации
cp "$HOME/$RELATIVE_API_PATH/README_API.md" "$TARGET_DIR/" 2>/dev/null || echo "Не найден README_API.md"

echo "=== Установка завершена ==="
echo "Ядро и подхваченные модули установлены в: $TARGET_DIR"
echo "Для запуска:"
echo "	cd $TARGET_DIR"
echo "	./bin/core"
