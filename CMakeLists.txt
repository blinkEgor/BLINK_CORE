cmake_minimum_required(VERSION 3.10)
project(ECS_CORE)

# 1. Сбор списка заголовков
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.h")

# 2. Сбор списка исходников
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")

# 3. Создание исполняемого файла
add_executable(core ${SOURCES} ${HEADERS})

# 4. Путь для #include
target_include_directories(core PRIVATE include)