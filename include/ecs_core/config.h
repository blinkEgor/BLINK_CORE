#pragma once
#include <string>
#include <unordered_map>
#include <fstream> // Чтение файлов
#include <sstream> // Парсинг строк
#include <iostream> // !!! УДАЛИТЬ КОГДА ПОЯВЯТСЯ ЛОГИ и система ввода/вывода CLI

namespace Config {
    bool load( const std::string& path = "configs/core.conf" );
    std::string get( const std::string& key, const std::string& fallback = "" );
    void print();
}