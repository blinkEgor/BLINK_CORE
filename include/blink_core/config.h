#pragma once
#include <string>
#include <unordered_map>
#include <fstream> // Чтение файлов
#include <sstream> // Парсинг строк
#include "logger.h"

namespace blink_config {
    bool load( const std::string& path = "configs/core.conf" );
    std::string get( const std::string& key, const std::string& fallback = "" );
    void print();
    void init();
}