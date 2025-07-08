#include "../../include/blink_core/config.h"

static std::unordered_map< std::string, std::string > config_map;
static std::unordered_set< std::string > dirty_keys;

bool blink_config::load( const std::string& path ) {
    blink_logger::log( "Loading config from: " + path, log_level::DEBUG );
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
            blink_logger::log( "Parsed config [" + current_key + "] = " + current_value, log_level::TRACE );
        }

        std::istringstream iss( line );
        std::string key, eq, value;

        if ( !( iss >> key >> eq ) ) continue;
        std::getline( iss, value );

        value.erase( 0, value.find_first_not_of( " \t" ) );
        value.erase( value.find_last_not_of( " \t" ) + 1 );

        if ( eq != "=" ) continue;

        blink_logger::log( "Found config key: " + key, log_level::DEBUG );
        current_key = key;
        current_value = value;
    }

    if ( !current_key.empty() ) {
        config_map[ current_key ] = current_value;
        blink_logger::log( "Parsed config [" + current_key + "] = " + current_value, log_level::TRACE );
    }

    return true;
}

std::string blink_config::get( const std::string& key, const std::string& fallback ) {
    if ( config_map.find( key ) != config_map.end() ) {
        blink_logger::log( "Get [" + key + "] = " + config_map[ key ], log_level::TRACE );
        return config_map[ key ];
    }
    blink_logger::log( "Get fallback for [" + key + "] = " + fallback, log_level::TRACE );
    return fallback;
}

void blink_config::print() {
    blink_cli::output( "[CONFIG]:\n" );
    for ( const auto& [ key, value ] : config_map ) {
        blink_cli::output( " " + key + " = " + value + "\n" );
    }
}

void blink_config::init() {
    blink_logger::log( "Initializing config system...", log_level::DEBUG );
    if ( blink_config::load() ) {
        blink_logger::log( blink_config::get( "config_init_message" ), log_level::INFO );

        bool cli_logging = blink_config::get( "cli_logging", "ON" ) == "ON";
        bool debug_logging = blink_config::get( "debug_logging", "ON" ) == "ON";

        blink_logger::configure( cli_logging, debug_logging );
    } else {
        blink_logger::log( "Config load failed in init()", log_level::WARNING );
    }
}

bool blink_config::set( const std::string& key, const std::string& value ) {
    if ( key.empty() ) {
        blink_logger::log( "Empty key provided", log_level::ERROR );
        return false;
    }

    if ( config_map.find( key ) != config_map.end() ) {
        config_map[ key ] = value;
        dirty_keys.insert( key );
        blink_logger::log( "Set [" + key + "] = " + config_map[ key ], log_level::TRACE );
        return true;
    }

    blink_logger::log( "Key [" + key + "] is not found!", log_level::ERROR );
    return false;
}

bool blink_config::save( const std::string& path ) {
    if ( dirty_keys.empty() ) {
        blink_logger::log( "No changes to save", log_level::DEBUG );
        return true;
    }

    blink_logger::log( "Saving config in: " + path, log_level::DEBUG );
    std::ifstream in_file( path );

    if ( !in_file.is_open() ) {
        blink_logger::log( "Failed to open config for reading: " + path, log_level::ERROR );
        // НА БУДУЩЕЕ, ТУТ СОЗДАТЬ КОНФИГ С ДЕФОЛТНЫМИ ОПЦИЯМИ И ЗНАЧЕНИЯМИ
        // ТОГДА НЕ ПРИДЕТСЯ ВОЗВРАЩАТЬ И МОЖНО ЗАМЕНИТЬ НА WARNING
        return false;
    }

    std::vector< std::string > lines;
    std::string line;
    while ( std::getline( in_file, line ) ) {
        lines.push_back( line );
    }
    in_file.close();

    std::string current_key;
    for( auto& line : lines ) {
        if ( line.empty() || line[0] == '#' ) continue;

        std::istringstream iss( line );
        std::string key, eq;
        if ( iss >> key >> eq && eq == "=" ) {
            current_key = key;
            if ( dirty_keys.count( key ) ) {
                line = key + " = " + config_map[ key ];
                dirty_keys.erase( key );
                blink_logger::log( "Saved new [key = value]: " + line, log_level::TRACE );
            }
        }
    }

    std::ofstream out_file( path );
    if ( !out_file.is_open() ) {
        blink_logger::log( "Failed to open config for writing: " + path, log_level::ERROR );
        // НА БУДУЩЕЕ, ТУТ СОЗДАТЬ КОНФИГ С ДЕФОЛТНЫМИ ОПЦИЯМИ И ЗНАЧЕНИЯМИ
        // ТОГДА НЕ ПРИДЕТСЯ ВОЗВРАЩАТЬ И МОЖНО ЗАМЕНИТЬ НА WARNING
        return false;
    }

    for ( const auto& line : lines ) {
        out_file << line << "\n";
    }
    out_file.close();

    blink_logger::log( "Config saved to: " + path, log_level::INFO );
    return true;
}