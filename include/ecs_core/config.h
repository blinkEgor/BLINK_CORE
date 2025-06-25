#pragma once
#include <string>
#include <unordered_map>

namespace Config {
    bool load( const std::string& path = "configs/core.conf" );
    std::string get( const std::string& key, const std::string& fallback = "" );
    void print();
}