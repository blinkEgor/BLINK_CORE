#include <iostream> // !!! Временно для печать в CLI
#include "../include/blink_core/arg_parser.h"
#include "../include/blink_core/config.h"
#include "../include/blink_core/logger.h"

int main( int argc, const char** argv ) {
    // === ИНИЦИАЛИЗАЦИЯ ЯДРА ===
    blink_logger::init();
    blink_config::init();
    if ( !arg_parser( argc, argv ) ) {
        blink_logger::log( "Parser can't load", log_level::FATAL );
        return 1;
    }

    // === ПОДКЛЮЧЕНИЕ API ===
    #ifdef ENABLE_BLINK_API
        // Инициализация API
    #endif

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
    blink_logger::shutdown();

    return 0;
}