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
				blink_cli::output( "Version: " + blink_config::get( "version" ) );
			}
			else if ( option == "--core-version" || option == "-core-v" ) {
				blink_cli::output( "Core version: " + blink_config::get( "blink_core_version" ) + "   From https://github.com/blinkEgor/BLINK_CORE/releases" );
			}
			else if ( option == "--api-version" || option == "-api-v" ) {
				blink_cli::output( "API version: " + blink_config::get( "blink_api_version" ) + "   From https://github.com/blinkEgor/" );
			}

		// ПОКАЗАТЬ значение ключа
			else if ( option == "--cli-logging" || option == "-cli" ) {
				blink_cli::output( "Status of CLI logging: " + blink_config::get( "cli_logging" ) );
			}
			else if ( option == "--debug-logging" || option == "-debug" ) {
				blink_cli::output( "Status of debugging: " + blink_config::get( "debug_logging" ) );
			}
			else if ( option == "--connect-loop-status" ) {
				blink_cli::output( "Connaction status of loop: " + blink_config::get( "connect_loop" ) );
			}
			else if ( option == "--main-loop-status" ) {
				blink_cli::output( "Status of <main_loop>: " + blink_config::get( "main_loop" ) );
			}

		// ИЗМЕНИТЬ значения ключа
			else if ( option == "--set-cli-logging" ) {
				std::string value = blink_cli::input( "Enter new value for cli_logging (ON/OFF): " );
				if ( value == "ON" || value == "OFF" ) {
					blink_config::set( "cli_logging", value );

				// Похоже на костыль, чтобы логгер использовал новые параметры, так же и в кофиге
					bool cli_logging = blink_config::get( "cli_logging", "ON" ) == "ON";
					bool debug_logging = blink_config::get( "debug_logging", "ON" ) == "ON";

					blink_logger::configure( cli_logging, debug_logging );
				} else {
					blink_logger::log( "Invalid value. Use ON/OFF", log_level::WARNING );
				}
			}
			else if ( option == "--set-debug-logging" ) {
				std::string value = blink_cli::input( "Enter new value for debug_logging (ON/OFF): " );
				if ( value == "ON" || value == "OFF" ) {
					blink_config::set( "debug_logging", value );

				// Похоже на костыль, чтобы логгер использовал новые параметры, так же и в кофиге
					bool cli_logging = blink_config::get( "cli_logging", "ON" ) == "ON";
					bool debug_logging = blink_config::get( "debug_logging", "ON" ) == "ON";

					blink_logger::configure( cli_logging, debug_logging );
				} else {
					blink_logger::log( "Invalid value. Use ON/OFF", log_level::WARNING );
				}
			}
			else if ( option == "--set-connect-loop" ) {
				std::string value = blink_cli::input( "Enter new value for connect_loop (ON/OFF): ");
				if ( value == "ON" || value == "OFF" ) {
					blink_config::set( "connect_loop", value );
				} else {
					blink_logger::log( "Invalid value. Use ON/OFF", log_level::WARNING );
				}
			}
			else if ( option == "--set-main-loop" ) {
				std::string value = blink_cli::input( "Enter new value for main_loop (start/stop): ");
				if ( value == "start" || value == "stop" ) {
					blink_config::set( "main_loop", value );
				} else {
					blink_logger::log( "Invalid value. Use start/stop", log_level::WARNING );
				}
			}
			else if ( option == "--set-api-path" ) {
				std::string value = blink_cli::input( "Enter path for <libblink_api.so> module: " );
				blink_config::set( "blink_api_path", value );
			}

		// DO ACTION
			else if ( option == "--save-core" ) {
				blink_config::save();
			}

			else {
				blink_cli::output( "Unknown argument: " + option );
				blink_cli::output( "Please write --help , to check available argument" );
			}
		}
	}

	blink_logger::log( "Arguments parsed successfully", log_level::INFO );
	blink_logger::log( "arg_parser is closing", log_level::DEBUG );
	return true;
}
