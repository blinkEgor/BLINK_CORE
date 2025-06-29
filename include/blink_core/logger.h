#pragma once

#include <fstream>  // Для работы с файлами
#include <filesystem> // Для работы с директориями
#include <iostream> // Для вывода в консоль
#include <chrono>   // Для работы со временем
#include <iomanip>  // Для форматирования вывода
#include <ctime>    // Для преобразования времени в строку
#include <vector>   // Для работы с вектором
#include <algorithm> // Для сортировки внутри вектора

// Перечисление для типов сообщений
enum class log_level {
    INFO,
    WARNING,
    ERROR,
    FATAL,
    DEBUG,
    TRACE,
};

namespace blink_logger {
    void cleanup_logs( int max_logs = 7 );
    std::string get_current_time();
    void log( const std::string& message, log_level level = log_level::INFO );
    void init();
    void shutdown();
}