#pragma once
#include <string>

class BLINK_API;
using ApiHandle = BLINK_API;

class ApiLoader {
public:
	ApiLoader( const std::string& path );
	~ApiLoader();

	bool load();
	void unload();

	bool init();
	void update();
	bool exit();

private:
	void* handle = nullptr;
	ApiHandle* api = nullptr;

	using create_api_t = ApiHandle* (*)();
	using destroy_api_t = void (*)(ApiHandle*);
	using api_init_t = bool (*)(ApiHandle*);
	using api_update_t = void (*)(ApiHandle*);
	using api_exit_t = bool (*)(ApiHandle*);

	create_api_t create_api = nullptr;
	destroy_api_t destroy_api = nullptr;
	api_init_t api_init = nullptr;
	api_update_t api_update = nullptr;
	api_exit_t api_exit = nullptr;

	std::string so_path;

	template<typename T>
	T load_symbol( const char* name );
};
