#include <iostream>

int main( int argc, const char** argv ) {
    // Тут проходит пересчёт аргументов и вызываются соответствующие команды или задаются настройки
    if ( argc > 1 ) {
        // Начинаю цикл с 1 потому что 0 - это имя программы.
        // Цикл гарантирует что каждый введенный аргумент будет просмотрен программой
        for ( int arg = 1; arg < argc; arg++ ) {
            std::string option = argv[ arg ];
            switch ( option[0] ) {  // Проверка первого символа одного аргумента
                case '-':
                    if ( ( option == "--help" ) || ( option == "-h" ) ) {
                        std::cout << "Help message\n"; // заглушка для списка возможных аргументов !!! ВРЕМЕННО !!!
                    }
                    else if ( ( option == "--version" ) || ( option == "-v" ) ) {
                        std::cout << "Version 1.0\n"; // заглушка для отображения актуальной версии программы !!! ВРЕМЕННО !!!
                    }
                    break;

                default:
                    std::cout << "Unknown argument: " << option << "\nPlease write --help option\n";
                    break;
            }
        }
    }

    std::cout << "Hello, CMake!" << std::endl;
    return 0;
}