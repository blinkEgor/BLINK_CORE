#include "../../include/blink_core/arg_parser.h"

bool arg_parser( int argc, const char** argv ) {
    blink_logger::log( "arg_parser is working...", log_level::DEBUG );
    if ( argc <= 1 ) {
        blink_logger::log( "No arguments passed", log_level::DEBUG );
        blink_logger::log( "arg_parser is closing", log_level::DEBUG );
        return true;
    }

    if ( argc > 1 ) {
        blink_logger::log( std::to_string( argc - 1 ) + " arguments submitted", log_level::DEBUG );
        for ( int arg = 1; arg < argc; arg++ ) {
            std::string option = argv[ arg ];
            blink_logger::log( std::to_string( arg ) + " argument is " + option, log_level::TRACE );

            if ( option == "--help" || option == "-h" ) {
                blink_cli::output( blink_config::get( "help_message" ) );
            }

            else if ( option == "--version" || option == "-v" ) {
                blink_cli::output( blink_config::get( "version" ) );
            }

            else {
                std::cout << "Unknown argument: " << option << "\nPlease write --help , to check available argument" << std::endl;
            }
        }
    }

    blink_logger::log( "Arguments parsed successfully", log_level::INFO );
    blink_logger::log( "arg_parser is closing", log_level::DEBUG );
    return true;
}