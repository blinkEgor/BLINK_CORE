#include "../include/blink_core/arg_parser.h"
#include "../include/blink_core/config.h"
#include "../include/blink_core/logger.h"
#include "../include/blink_core/api_runtime.h"
#include "../include/main_loop.h"

int main( int argc, const char** argv ) {
	// === ИНИЦИАЛИЗАЦИЯ ЯДРА ===
	blink_logger::init();
	blink_config::init();
	if ( !arg_parser( argc, argv ) ) {
		blink_logger::log( "Parser can't load", log_level::FATAL );
		return 1;
	}

	// === ПОДКЛЮЧЕНИЕ API ===
	std::string api_path = blink_config::get( "blink_api_path", "bin/libblink_api.so" );
	if ( blink_api_runtime::init( api_path ) ) {
		blink_logger::log( "API module was connected", log_level::INFO );
	} else {
		blink_logger::log( "API module was not connected", log_level::ERROR );
	}

	// === ИНИЦИАЛИЗАЦИЯ ВНЕШНИХ ЗАВИСИМОСТЕЙ ===
	#ifdef ENABLE_SDL2
		// Инициализация SDL2
	#endif

	// === ГЛАВНЫЙ ЦИКЛ ===

	std::string connect_loop = blink_config::get( "connect_loop", "OFF" );
	bool is_connect_loop = connect_loop == "ON";
	if ( is_connect_loop ) {
		if ( main_loop::loop() ) {
			blink_logger::log( "Main loop was closed", log_level::INFO );
		}
	} else {
		blink_logger::log( "Connecting loop was <" + std::string( is_connect_loop ? "true" : "false" ) + ">, bacaus connect_loop was <" + connect_loop, log_level::DEBUG );
	}

	// === ВЫХОД ИЗ ПРОГРАММЫ ===

	#ifdef ENABLE_SDL2
		// Закрытие SDL2
	#endif

	// В самом конце для финалной отладки (с лога начали, логом закончили)
	blink_api_runtime::shutdown();
	blink_logger::shutdown();

	return 0;
}
