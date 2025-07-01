#include "../../include/blink_core/logger.h"

static bool cli_enabled = true;
static bool debug_enabled = true;

void blink_logger::cleanup_logs( int max_logs ) {
    if ( max_logs <= 0 ) {
        max_logs = 7;
    }

    namespace fs = std::filesystem;
    std::vector<fs::directory_entry> logs;

    for ( const auto& entry : fs::directory_iterator( "logs" ) ) {
        if ( entry.is_regular_file() && entry.path().extension() == ".txt" ) {
            logs.push_back( entry );
        }
    }

    std::sort( logs.begin(), logs.end(), []( const auto& a, const auto& b ) {
        return fs::last_write_time( a ) > fs::last_write_time( b );
    } );

    for ( size_t i = max_logs; i < logs.size(); ++i ) {
        fs::remove( logs[i] );
    }
}

std::string blink_logger::get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t( now );
    std::tm now_tm = *std::localtime( &now_time_t );
    std::stringstream ss;
    ss << std::put_time( &now_tm, "%Y-%m-%d %H:%M:%S" );
    return ss.str();
}

void blink_logger::log( const std::string& message, log_level level ) {
    if ( !debug_enabled && ( level == log_level::DEBUG || level == log_level::TRACE ) ) {
        return;
    }

    std::string time_str = get_current_time();
    std::string level_str;

    switch ( level ) {
        case log_level::INFO: level_str = "[INFO] "; break;
        case log_level::WARNING: level_str = "[WARNING] "; break;
        case log_level::ERROR: level_str = "[ERROR] "; break;
        case log_level::FATAL: level_str = "[FATAL] "; break;
        case log_level::DEBUG: level_str = "[DEBUG] "; break;
        case log_level::TRACE: level_str = "[TRACE] "; break;
        default: level_str = "[UNKNOWN] "; break;
    }
    if ( !std::filesystem::exists( "logs" ) ) {
        std::filesystem::create_directory( "logs" );
    }
    std::string date_str = blink_logger::get_current_time().substr( 0, 10 );
    std::string filename = "logs/log_" + date_str + ".txt";
    std::ofstream log_file( filename, std::ios::app );
    if ( log_file.is_open() ) {
        log_file << "[" << time_str << "] " << level_str << message << std::endl;
        log_file.close();
    }
    if ( cli_enabled ) {
        std::cerr << "[" << time_str << "] " << level_str << message << std::endl;
    }
}

void blink_logger::init() {
    if ( !std::filesystem::exists( "logs" ) ) {
        std::filesystem::create_directory( "logs" );
    }
    cleanup_logs();
    log( "blink_logger initialized", log_level::INFO );
}

void blink_logger::shutdown() {
    std::ofstream log_file( "logs/log_" + get_current_time().substr( 0, 10 ) + ".txt", std::ios::app );
    if ( log_file.is_open() ) {
        log_file << std::endl;
        log_file.close();
    }
    std::cerr << std::endl;
}

void blink_logger::configure( bool enable_cli, bool enable_debug ) {
    cli_enabled = enable_cli;
    debug_enabled = enable_debug;
}