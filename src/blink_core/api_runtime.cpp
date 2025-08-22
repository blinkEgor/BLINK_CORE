#include "../../include/blink_core/api_runtime.h"
#include "../../include/blink_core/logger.h"

std::unique_ptr<ApiLoader> blink_api_runtime::loader = nullptr;

bool blink_api_runtime::init( const std::string& path ) {
	loader = std::make_unique<ApiLoader>( path );
	if ( !loader->load() ) {
		blink_logger::log( "API load failed", log_level::FATAL );
		loader.reset();
		return false;
	}
	return loader->init();
}


void blink_api_runtime::shutdown() {
	if ( loader ) {
		loader->exit();
		loader.reset();	// вызовет ApiLoader::~ApiLoader -> unload()
	}
}
