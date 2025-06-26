#include "../../include/ecs_core/config.h"

static std::unordered_map< std::string, std::string > config_map;

// ### Функция принимает параметр адреса, где находится конфиг, и имеет значение по умолчанию для core.conf
// Выполняет действия: 
// - Читает файл по заданному адресу
// - Проверяет пустую строку или комментарий
// - Парьсит строку
// - - Извлекает ключь до первого пробела
// - - Извлекает символ "="
// - - Извлекает остаток строки как значение
bool Config::load( const std::string& path ) {
    std::ifstream file( path );

    if ( !file.is_open() ) {
        // !!! ЗАМЕНИТЬ НА ЛОГ
        std::cerr << "[ERROR] Failed to open config: " << path << std::endl;
        return false;
    }

    std::string line;
    while ( std::getline( file, line ) ) {
        if ( line.empty() || line[0] == '#' ) continue;

        std::istringstream iss( line );
        std::string key, eq, value;

        if ( !( iss >> key >> eq ) ) continue;

        std::getline( iss, value );

        if ( eq != "=" ) continue;

        config_map[ key ] = value;
    }
    
    return true;
}

// ### Функция принимает параметр ключа и значение для ключа по умолчанию
// Выполняет действия: 
// - Ищит в словаре ключей и значений нужный заданный параметром ключ и возвращает значение
// - Если ключ не найден, то вернёт значение по умолчанию
std::string Config::get( const std::string& key, const std::string& fallback ) {
    if ( config_map.find( key ) != config_map.end() ) return config_map[ key ];
    return fallback;
}

// ### Функция не принимает и не возвращает значения
// Выполняет действия: 
// - Печатает сообщение о том что будет напечатано содержимое конфига
// - Построчно печатает содержимое конфига
void Config::print() {
    // !!! Заменить на систему ввода/вывода CLI
    std::cout << "[CONFIG]:\n";
    for ( const auto& [ key, value ] : config_map ) {
        // !!! Заменить на систему ввода/вывода CLI
        std::cout << " " << key << " = " << value << std::endl; 
    }
}