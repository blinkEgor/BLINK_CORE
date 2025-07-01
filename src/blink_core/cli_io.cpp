#include "../../include/blink_core/cli_io.h"

std::string blink_cli::input() {
    std::string input;
    if ( !( std::cin >> input ) ) {
        blink_logger::log( "Failed to read input (stream error)", log_level::WARNING );
        std::cin.clear();
        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        return "";
    }
    blink_logger::log( "Input is: " + input, log_level::TRACE );
    return input;
};

void blink_cli::output( std::string message ) {
    std::cout << message << std::endl;
    blink_logger::log( "Output message is: " + message, log_level::TRACE );
}