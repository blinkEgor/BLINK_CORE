#include <iostream> // !!! Временно для печать в CLI
#include "../include/ecs_core/arg_parser.h"
#include "../include/ecs_core/config.h"

int main( int argc, const char** argv ) {
    if ( !parse_args( argc, argv ) ) {
        // Тут лог ошибки
        std::cerr << "[ERROR] " << std::endl;
        return 1;
    }

    Config::load();
    std::cout << Config::get( "greeting_message" ) << std::endl;
    return 0;
}