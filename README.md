# ECS_CORE
This is my personal repository for creating a game/program core using ECS ​​pattern.


## Описание архитектуры ядра
- main.cpp - Обработка argv[], запуск ядра, логирование
- config.* - Чтение и (опционально) сохранение core.conf
- logger.* - Вывод в консоль и/или файл, с уровнями логов
- core_loop.* - Цикл ядра: Init() → while() → Shutdown()
- core.conf - Описание параметров работы: enable_api = true и т.п.
- include/ecs_core/ - Хедеры, экспортируемые наружу (другим частям движка)