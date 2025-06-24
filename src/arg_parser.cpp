#include "../include/ecs_core/arg_parser.h"

bool parse_args( int argc, const char** argv ) {
    // Нет аргументов — идём в цикл
    if ( argc <= 1 ) return true;

    // Временные переменные, будут заменены данными из конфига и вшитыми параметрами версий
    const std::string version = "1.0";
    const std::string stage = "-alpha";
    
    const std::string help_message = "Hellp message: \n --version / -v   Show programm version [v]-[NUMBER]-[STAGE]";
    // -----------------------------------------------------------------------------------

    // Тут проходит пересчёт аргументов и вызываются соответствующие команды или задаются настройки
    if ( argc > 1 ) {
        // Начинаю цикл с 1 потому что 0 - это имя программы.
        // Цикл гарантирует что каждый введенный аргумент будет просмотрен программой
        for ( int arg = 1; arg < argc; arg++ ) {
            std::string option = argv[ arg ];

            if ( option == "--help" || option == "-h" ) {
                std::cout << help_message << std::endl;
            }

            else if ( option == "--version" || option == "-v" ) {
                std::cout << "v-" << version << stage << std::endl; 
            }

            else {
                std::cout << "Unknown argument: " << option << "\nPlease write --help , to check available argument" << std::endl;
            }
        }
    }

    // Выход полсе перебора всех аргументов
    return true;
}