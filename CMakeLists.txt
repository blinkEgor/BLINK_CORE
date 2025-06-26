# Этот строка говорит CMake, что для сборки нужна не менее чем 3.16-я версия CMake.
cmake_minimum_required(VERSION 3.16)

# Это объявляет проект ECS_CORE
# VERSION 0.1 — это назначенная точка разработки
# LANGUAGES CXX — проект на C++
project(ECS_CORE VERSION 0.1 LANGUAGES CXX)

# Конфигурация сборки
set(CMAKE_CXX_STANDARD 17)              # Требуемый стандарт C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Не разрешать откат на более старые стандарты
set(CMAKE_BUILD_TYPE Debug)             # Сборка в режиме Debug по умолчанию

# ОС Linux по умолчанию
add_definitions(-DTARGET_OS_LINUX)

# Имя исполняемого файла (бинарника)
if (NOT DEFINED BINARY_NAME)
    set(BINARY_NAME "core")
endif()

# Пути к исходникам
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Где .h-файлы
include_directories(${INCLUDE_DIR})

# Опции для будущих расширений
option(ENABLE_SDL2 "Connect SDL2" OFF)

if (ENABLE_SDL2)
    message(STATUS "SDL2 is ON")
    add_definitions(-DENABLE_SDL)
endif()

# Файлы с исходниками ядра
file(GLOB_RECURSE ECS_CORE_SRC
    ${SRC_DIR}/ecs_core/*.cpp
)

# Сборка бинарника
add_executable(${BINARY_NAME}
    ${SRC_DIR}/main.cpp
    ${ECS_CORE_SRC}
)

# Где будет оказываться готовый бинарник
set(OUTPUT_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR}
)

# Выбор ОС под которую будет создан бинарник
if (TARGET_OS STREQUAL "linux")
    add_definitions(-DTARGET_OS_LINUX)
elseif(TARGET_OS STREQUAL "windows")
    add_definitions(-DTARGET_OS_WINDOWS)
# Тут продолжать другие ОС
endif()

# Сообщение после успешной сборки
message(STATUS "ECS_CORE core ${BINARY_NAME} built for ${TARGET_OS}")