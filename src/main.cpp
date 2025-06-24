#include <iostream>
#include "../include/ecs_core/arg_parser.h"

int main( int argc, const char** argv ) {
    if ( !parse_args( argc, argv ) ) {
        // Тут лог ошибки
        return 1;
    }

    std::cout << "Hello, I'Core!" << std::endl;
    return 0;
}