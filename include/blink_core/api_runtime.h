#pragma once
#include "api_loader.h"
#include <memory>
#include <string>

namespace blink_api_runtime {
	extern std::unique_ptr<ApiLoader> loader;

	bool init( const std::string& path );
	void shutdown();
}
