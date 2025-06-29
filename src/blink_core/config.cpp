#include "../../include/blink_core/config.h"

static std::unordered_map< std::string, std::string > config_map;

bool blink_config::load( const std::string& path ) {
    std::ifstream file( path );

    if ( !file.is_open() ) {
        blink_logger::log( "Failed to open config: " + path, log_level::ERROR );
        // НА БУДУЩЕЕ, ТУТ СОЗДАТЬ КОНФИГ С ДЕФОЛТНЫМИ ОПЦИЯМИ И ЗНАЧЕНИЯМИ
        // ТОГДА НЕ ПРИДЕТСЯ ВОЗВРАЩАТЬ И МОЖНО ЗАМЕНИТЬ НА WARNING
        return false;
    }

    std::string current_key;
    std::string current_value;

    std::string line;
    while ( std::getline( file, line ) ) {
        if ( line.empty() || line[0] == '#' ) continue;

        if ( !current_key.empty() && ( line[0] == ' ' || line[0] == '\t' ) ) {
            current_value += "\n" + line;
            continue;
        }

        if ( !current_key.empty() ) {
            config_map[ current_key ] = current_value;
        }

        std::istringstream iss( line );
        std::string key, eq, value;

        if ( !( iss >> key >> eq ) ) continue;
        std::getline( iss, value );

        value.erase( 0, value.find_first_not_of( " \t" ) );
        value.erase( value.find_last_not_of( " \t" ) + 1 );

        if ( eq != "=" ) continue;

        current_key = key;
        current_value = value;

    }

    if ( !current_key.empty() ) {
        config_map[ current_key ] = current_value;
    }
    
    return true;
}

std::string blink_config::get( const std::string& key, const std::string& fallback ) {
    if ( config_map.find( key ) != config_map.end() ) return config_map[ key ];
    return fallback;
}

void blink_config::print() {
    // !!! Заменить на систему ввода/вывода CLI
    std::cout << "[CONFIG]:\n";
    for ( const auto& [ key, value ] : config_map ) {
        // !!! Заменить на систему ввода/вывода CLI
        std::cout << " " << key << " = " << value << std::endl; 
    }
}

void blink_config::init() {
    blink_config::load();
    blink_logger::log( blink_config::get( "config_init_message" ), log_level::INFO );
}