#include "../../include/blink_core/logger.h"

// ### функция для удаления устаревших логов
// - Кэширование пространства имён "std::filesystem" в псевдониме "fs"
// - Создание временного списка всех файлов логов в директории "logs"
// - - Сканируется только "logs/"
// - - В список попадают только обычные файлы с расширением ".txt"
// - Сортировка списка по времени последнего изменения
// - - Сначала идут новые файлы ( новее = выше )
// - Удаление всех логов, начиная с позиции "max_logs"
// - - Пример: если файлов 10, а max_logs = 7 → удалятся последние 3
// - - Удаление происходит через "fs::remove()"
void blink_logger::cleanup_logs( int max_logs ) {
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

// ### Функция для получения текущего времени в формате "гггг-мм-дд чч:мм:сс"
// - Получение текущего времени
// - Преобразование в time_t (время в секундах)
// - Преобразование в структуру tm ( для форматирования )
// - Использование stringstream для форматирования
// - Возвращаемый формат: "гггг-мм-дд чч:мм:сс"
std::string blink_logger::get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t( now );
    std::tm now_tm = *std::localtime( &now_time_t );
    std::stringstream ss;
    ss << std::put_time( &now_tm, "%Y-%m-%d %H:%M:%S" );
    return ss.str();
}

// ### Функция для логирования по уровням в файл и cli
// - Получение текущего времени ( get_current_time() )
// - Определение префикса в зависимости от уровня логирования
// - Создание директории логов, если её нет
// - Создание имени файла, с сортировкой по дням
// - Открытие файла для записи ( добавление новых строк в конец файла )
// - Записывание сообщения в файл
// - - Вывод ошибки в cli, при невозможности открыть файл лога
// - Вывод сообщения в cli
void blink_logger::log( const std::string& message, log_level level ) {
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
    if( log_file.is_open() ) {
        log_file << "[" << time_str << "] " << level_str << message << std::endl;
        log_file.close();
    } else {
        std::cerr << "[" << time_str << "] " << "[ERROR] Failed to open log file!" << std::endl;
    }
    std::cerr << "[" << time_str << "] " << level_str << message << std::endl;
}

// ### Функция инициализации системы логирования на уровне ЯДРА
// 1. Создать папку logs, если её нет
// 2. Очистить старые логи
// 3. Лог: начало новой сессии
void blink_logger::init() {
    if ( !std::filesystem::exists( "logs" ) ) {
        std::filesystem::create_directory( "logs" );
    }
    cleanup_logs();
    log( "blink_logger initialized", log_level::INFO );
}

// ### Простая функция задача которой во время логирования в конце сессии добавить отступ
void blink_logger::shutdown() {
    std::ofstream log_file( "logs/log_" + get_current_time().substr( 0, 10 ) + ".txt", std::ios::app );
    if ( log_file.is_open() ) {
        log_file << std::endl;
        log_file.close();
    }
    std::cerr << std::endl;
}