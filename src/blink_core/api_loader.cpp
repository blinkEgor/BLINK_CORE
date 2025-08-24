#include "../../include/blink_core/api_loader.h"
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>
#include "../../include/blink_core/logger.h"

ApiLoader::ApiLoader( const std::string& path ) : so_path( path ) {}

ApiLoader::~ApiLoader() {
	unload();
}

bool ApiLoader::load() {
	handle = dlopen( so_path.c_str(), RTLD_LAZY );
	if ( !handle ) {
		blink_logger::log( "dlopen failed: " + std::string( dlerror() ), log_level::FATAL );
		return false;
	}

	create_api = load_symbol<create_api_t>( "create_api" );
	destroy_api = load_symbol<destroy_api_t>( "destroy_api" );
	api_init = load_symbol<api_init_t>( "api_init" );
	api_update = load_symbol<api_update_t>( "api_update" );
	api_exit = load_symbol<api_exit_t>( "api_exit" );

	api = create_api();
	if ( !api ) {
		blink_logger::log( "create_api() returned nullptr", log_level::FATAL );
		return false;
	}

	blink_logger::log( "API symbols loaded successfully", log_level::INFO );

	return true;
}

void ApiLoader::unload() {
	if ( api && destroy_api ) {
		destroy_api( api );
		api = nullptr;
	}
	if ( handle ) {
		dlclose( handle );
		handle = nullptr;
	}
}

bool ApiLoader::init() {
	return api && api_init ? api_init( api ) : false;
}

void ApiLoader::update() {
	if ( api && api_update ) api_update( api );
}

bool ApiLoader::exit() {
	return api && api_exit ? api_exit( api ) : false;
}

template<typename T>
T ApiLoader::load_symbol( const char* name ) {
	dlerror();	// очистить старую ошибку
	T symbol = reinterpret_cast<T>( dlsym( handle, name ) );
	const char* error = dlerror();
	if ( error ) {
		throw std::runtime_error( "dlsym failed for " + std::string( name ) + ": " + error );
	}
	return symbol;
}
