# ECS_CORE
This is my personal repository for creating a game/program core using ECS ​​pattern.


## Описание архитектуры ядра
- main.cpp - Обработка argv[], запуск ядра, логирование
- config.* - Чтение и (опционально) сохранение core.conf
- logger.* - Вывод в консоль и/или файл, с уровнями логов
- core_loop.* - Цикл ядра: Init() → while() → Shutdown()
- core.conf - Описание параметров работы: enable_api = true и т.п.
- include/ecs_core/ - Хедеры, экспортируемые наружу (другим частям движка)

## Описание файла сборки - CMakeLists.txt
- cmake_minimum_required(VERSION…) - Минимальная версия CMake, с которой можно собирать
- project(...) - Имя проекта и язык
- set(CMAKE_CXX_STANDARD 17) - Явно указывает, что C++17 нужен
- set(CMAKE_BUILD_TYPE Debug) - По умолчанию дебаг-сборка, можно менять на Release
- set(SRC_DIR …) - Удобные переменные для путей
- include_directories(...) - Сообщает компилятору, где лежат #include "ecs_core/*.h"
- add_executable(...) - Собирает исполняемый файл "бинарник" из указанных .cpp
- set_target_properties(...) - Кладёт готовый "бинарник" в build/bin/ после сборки
- message(...) - Просто для красивого вывода в терминале