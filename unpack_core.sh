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

# Запрос пути к libblink_api.so (относительно домашней)
echo "Введите путь к директории с libblink_api.so относительно домашней директории: "
read RELATIVE_API_PATH
API_PATH="$HOME/$RELATIVE_API_PATH/libblink_api.so"

if [ -f "$API_PATH" ]; then
	cp "$API_PATH" "$TARGET_DIR/bin/"
	echo "libblink_api.so скопирован"
else
	echo "Внимание: libblink_api.so не найден по пути: $API_PATH! Необходимо установить его отдельно в $TARGET_DIR/bin/."
fi

echo "=== Установка завершена ==="
echo "Ядро и подхваченные модули установлены в: $TARGET_DIR"
echo "Для запуска:"
echo "	cd $TARGET_DIR"
echo "	./bin/core"
