#include "../../include/blink_core/arg_parser.h"

bool arg_parser( int argc, const char** argv ) {
    if ( argc <= 1 ) return true;

    if ( argc > 1 ) {
        // Начинаю цикл с 1 потому что 0 - это имя программы.
        // Цикл гарантирует что каждый введенный аргумент будет просмотрен программой
        for ( int arg = 1; arg < argc; arg++ ) {
            std::string option = argv[ arg ];

            if ( option == "--help" || option == "-h" ) {
                std::cout << blink_config::get( "help_message" ) << std::endl;
                blink_logger::log( "Print help message: " + blink_config::get( "help_message" ), log_level::TRACE );
            }

            else if ( option == "--version" || option == "-v" ) {
                std::cout << blink_config::get( "version" ) << std::endl;
                blink_logger::log( "Version: " + blink_config::get( "version" ), log_level::TRACE );
            }

            else {
                std::cout << "Unknown argument: " << option << "\nPlease write --help , to check available argument" << std::endl;
            }
        }
    }

    return true;
}