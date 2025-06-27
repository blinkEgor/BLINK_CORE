#include <iostream> // !!! Временно для печать в CLI
#include "../include/ecs_core/arg_parser.h"
#include "../include/ecs_core/config.h"
#include "../include/ecs_core/logger.h"

int main( int argc, const char** argv ) {
    // === ИНИЦИАЛИЗАЦИЯ ЯДРА ===
    Logger::init();
    Config::init();
    if ( !parse_args( argc, argv ) ) {
        Logger::log( "Parser can't load", LogLevel::FATAL );
        return 1;
    }

    // === ПОДКЛЮЧЕНИЕ API ===
    
    // ПОКА ЧТО НЕ СУЩЕСТВУЕТ


    // === ИНИЦИАЛИЗАЦИЯ ЗАВИСИМОСТЕЙ ===
    #ifdef ENABLE_SDL2
        // Инициализация SDL2
    #endif

    // === ГЛАВНЫЙ ЦИКЛ ===

    // ПОКА ЧТО НЕ СУЩЕСТВУЕТ

    // === ВЫХОД ИЗ ПРОГРАММЫ ===

    #ifdef ENABLE_SDL2
        // Закрытие SDL2
    #endif
    
    // В самом конце для финалной отладки (с лога начали, логом закончили)
    Logger::shutdown();

    return 0;
}