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

# Запрос целевой директории
echo "Введите путь для установки (абсолютный путь или относительный, например: ~/myproject или /path/to/project): "
read TARGET_PATH
TARGET_DIR="${TARGET_PATH//\~/$HOME}"	# Замена тильды(~) на $HOME

mkdir -p "$TARGET_DIR"

# Копирование файлов из текущей директории
echo "Копирование файлов ядра..."
cp -r bin configs include "$TARGET_DIR"/
cp -f LICENSE "$TARGET_DIR"/

# Определение методов необходимые для установки API
check_unzip() {
	if ! command -v unzip &> /dev/null; then
		echo "Ошибка: unzip не установлен. Установите его и повторите попытку."
		exit 1
	fi
}
check_wget() {
	if ! command -v wget &> /dev/null; then
		echo "Ошибка: wget не установлен. Установите его и повторите попытку."
		exit 1
	fi
}

# Запрос пути к libblink_api.so и API (dist-dir, not src)
echo "У вас скачен API (dist директория)? (y/n):"
read HAVE_API
DEFAULT_PATH="$HOME/Downloads"
API_DIR_FULL=""	# чтобы область видимости была глобальной

if [ "$HAVE_API" = "n" ]; then
	# Прорерка кэша распакованной директории
	if [ -d "$DEFAULT_PATH/API" ]; then
		API_DIR_FULL="$DEFAULT_PATH/API"
	else
		# Проверка кэша zip архива
		if [ -f "$DEFAULT_PATH/API.zip" ]; then
			check_unzip
			unzip "$DEFAULT_PATH/API.zip" -d "$DEFAULT_PATH"
			API_DIR_FULL="$DEFAULT_PATH/API"
		else
			check_wget
			wget -O "$DEFAULT_PATH/API.zip" https://github.com/blinkEgor/BLINK_API/releases/download/v0.1.0-proto/API.zip
			check_unzip
			unzip "$DEFAULT_PATH/API.zip" -d "$DEFAULT_PATH"
			API_DIR_FULL="$DEFAULT_PATH/API"
		fi
	fi
else
	echo "Введите путь к директории API (абсолютный или относительный, например: ~/Downloads/API): "
	read API_DIR_PATH
	API_DIR_FULL="${API_DIR_PATH//\~/$HOME}"	# Замена тильды(~) на $HOME
fi

API_PATH="$API_DIR_FULL/bin/libblink_api.so"

if [ -f "$API_PATH" ]; then
	cp "$API_PATH" "$TARGET_DIR/bin/"
	echo "libblink_api.so скопирован"

	# Копирование файлов API
	echo "Копирование файлов API..."
	API_INCLUDE_DIR="$TARGET_DIR/include/blink_api"
	mkdir -p "$API_INCLUDE_DIR/abstractions"
	mkdir -p "$API_INCLUDE_DIR/stubs"
	mkdir -p "$TARGET_DIR/configs/api_plugins"

	# Копирование заголовочных файлов
	cp -r "$API_DIR_FULL/include/blink_api/abstractions"/*.h "$API_INCLUDE_DIR/abstractions/" 2>/dev/null || echo "Не найдены файлы abstractions"
	cp -r "$API_DIR_FULL/include/blink_api/stubs"/*.h "$API_INCLUDE_DIR/stubs/" 2>/dev/null || echo "Не найдены файлы stubs"
	cp "$API_DIR_FULL/include/blink_api/api.h" "$API_INCLUDE_DIR/" 2>/dev/null || echo "Не найден api.h"
	cp "$API_DIR_FULL/include/blink_api/version.h" "$API_INCLUDE_DIR/" 2>/dev/null || echo "Не найден version.h"

	# Копирование конфигов
	cp "$API_DIR_FULL/configs/api_plugins"/*.conf "$TARGET_DIR/configs/api_plugins/" 2>/dev/null || echo "Не найдены конфиги api_plugins"

	# Копирование документации
	cp "$API_DIR_FULL/README_API.md" "$TARGET_DIR/" 2>/dev/null || echo "Не найден README_API.md"
else
	echo "Внимание: libblink_api.so не найден по пути: $API_PATH! Необходимо установить его отдельно в $TARGET_DIR/bin/."
fi

# Получается, примерно тут конец этойго выбора, дальше всё по инструкции как было. Но лучше перепровирить логику!!!
# Например, я сейчас смотрю и вижу, что ниже написано "Копирование файлов API", а выше я вижу, что "libblink_api.so" 
# тоже является частью API но копируется в первую очередь... Может следует "Копирование файлов API" логику 
# вписать в этот блок проверки ? Нужна консультация по этому поводу. Если "API_PATH" не содержит самой библиотеки, 
# то зачем остальное создавать и копировать, будет лучше пропустить это и установить вручную... Хотя, благодаря 
# этой фичи, которую я сейчас хочу сделать, не придется вречную устанавливать, потому что он скачает целый, 
# dist репозиторий API в котором точно будут все нужные файлы... Разве что скачать отдельно другую версия вручную.

echo "=== Установка завершена ==="
echo "Ядро и подхваченные модули установлены в: $TARGET_DIR"
echo "Для запуска:"
echo "	cd $TARGET_DIR"
echo "	./bin/core # если у вас стандартныое имя исполняемого файла"
