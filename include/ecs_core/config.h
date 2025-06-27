#pragma once
#include <string>
#include <unordered_map>
#include <fstream> // Чтение файлов
#include <sstream> // Парсинг строк
#include "logger.h"

namespace Config {
    bool load( const std::string& path = "configs/core.conf" );
    std::string get( const std::string& key, const std::string& fallback = "" );
    void print();
    void init();
}