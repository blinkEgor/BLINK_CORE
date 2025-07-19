#!/bin/bash
# ----------------------------------------
# pack-core.sh — упаковка ядра BLINK_CORE для релиза
# Автор: Егор
# 
# Инструкция: 
#   chmod +x pack_core.sh           # дать права
#   ./pack_core.sh                  # запустить
#   unzip -l dist/BLINK_CORE.zip    # распокавать
# ----------------------------------------

# === ПАРАМЕТРЫ ===

EXECUTABLE_BIN="core"
ZIP_NAME="BLINK_CORE"

LIBRARY_BIN="libblink_core.so"

DIST_DIR="dist"
BIN_DIR="bin"
CONFIG_DIR="configs"
INCLUDE_DIR="include"
INCLUDE_BLINK_CORE_DIR="blink_core"

INCLUDE_MAIN_LOOP_FILE="main_loop.h"
CONFIG_CORE_FILE="core.conf"
ARCHITECTURE_FILE="ARCHITECTURE.md"
README_CORE_FILE="README_CORE.md"
UNPACK_CORE_FILE="unpack_core.sh"

if [ ! -z "$1" ]; then
    EXECUTABLE_BIN=$1
fi
if [ ! -z "$2" ]; then
    ZIP_NAME=$2
fi

# ===================

# === ПРОВЕРКИ ===
echo "=== Checking files ==="

check_file() {
    if [ ! -f "$1" ] && [ ! -d "$1" ]; then
        echo "[ERROR] File/directory not found: $1"
        return 1
    fi
    return 0
}

check_file "$BIN_DIR/$EXECUTABLE_BIN" || exit 1
check_file "$BIN_DIR/$LIBRARY_BIN" || exit 1
check_file "$CONFIG_DIR/$CONFIG_CORE_FILE" || exit 1
check_file "$README_CORE_FILE" || exit 1
check_file "$INCLUDE_DIR/$INCLUDE_BLINK_CORE_DIR" || exit 1

# ===================

# === СОЗДАНИЕ ===
echo "=== Creating a structure in $DIST_DIR ==="

mkdir -p $DIST_DIR/$BIN_DIR
mkdir -p $DIST_DIR/$CONFIG_DIR
mkdir -p $DIST_DIR/$INCLUDE_DIR/$INCLUDE_BLINK_CORE_DIR

# ===================

# === КОПИРОВАНИЕ ===
echo "=== Copying files ==="

copy_with_check() {
    local src=$1
    local dst=$2
    if check_file "$src"; then
        cp -f "$src" "$dst" && echo "[OK] $src -> $dst"
    else
        echo "[MISSED] $src not found"
    fi
}

# Бинарники
copy_with_check "$BIN_DIR/$EXECUTABLE_BIN" "$DIST_DIR/$BIN_DIR/"
copy_with_check "$BIN_DIR/$LIBRARY_BIN" "$DIST_DIR/$BIN_DIR/"

# Конфиги
copy_with_check "$CONFIG_DIR/$CONFIG_CORE_FILE" "$DIST_DIR/$CONFIG_DIR/"

# Заголовки (рекурсивно)
if [ -d "$INCLUDE_DIR/$INCLUDE_BLINK_CORE_DIR" ]; then
    cp -r "$INCLUDE_DIR/$INCLUDE_BLINK_CORE_DIR/"* "$DIST_DIR/$INCLUDE_DIR/$INCLUDE_BLINK_CORE_DIR/" && echo "[OK] Headers copied"
else
    echo "[ERROR] Directory with headers not found"
    exit 1
fi
copy_with_check "$INCLUDE_DIR/main_loop.h" "$DIST_DIR/$INCLUDE_DIR/"

# Документация
copy_with_check "$README_CORE_FILE" "$DIST_DIR/"

# Скрипт распаковки
if [ -f "$UNPACK_CORE_FILE" ]; then
    cp -f "$UNPACK_CORE_FILE" "$DIST_DIR/" && echo "[OK] $UNPACK_CORE_FILE added"
else
    echo "[INFO] $UNPACK_CORE_FILE not found, skipping"
fi

# ===================

# === ЗАПАКОВКА В АРХИВ ZIP ===
echo "=== Creating an archive ==="

cd "$DIST_DIR" || exit 1
zip -r "$ZIP_NAME.zip" ./* > /dev/null && echo "[OK] Archive created: BLINK_CORE.zip" || echo "[ERROR] Failed to create archive"
cd ..

# === ИТОГ ===
echo "=== Ready! ==="

echo "Result: $DIST_DIR/BLINK_CORE.zip"

# ===================
