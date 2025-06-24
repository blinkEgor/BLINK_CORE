cmake_minimum_required(VERSION 3.16)

# Название проекта и версия
project(ECS_CORE VERSION 0.1 LANGUAGES CXX)

# Конфигурация сборки
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug) # По умолчанию "Debug"

# ОС по умлочанию
add_definitions(-DTARGET_OS_LINUX)

# Имя исполняемого файла (бинарника)
if (NOT DEFINED BINARY_NAME)
    set(BINARY_NAME "core")
endif()

# Пути к исходникам
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Где .h-файлы (public API)
include_directories(${INCLUDE_DIR})

# Опции расширения в будущем (временно отключены)
option(ENABLE_API "Подключить API" OFF)
option(ENABLE_SDL "Подключить SDL" OFF)

if (ENABLE_API)
    message(STATUS "API включено")
    add_definitions(-DENABLE_API)
endif()

# Сборка бинарника
add_executable(${BINARY_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/config.cpp
    ${SRC_DIR}/logger.cpp
    ${SRC_DIR}/core_loop.cpp
    ${SRC_DIR}/arg_parser.cpp
)

# ../bin относительно папки сборки
set(OUTPUT_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

# Установка бинарника в bin/
set_target_properties(${BINARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR}
)

# Выбор операционной системы под которую будет создан бинарник
if (UNIX AND NOT APPLE)
    set(TARGET_OS "linux")
    add_definitions(-DTARGET_OS_LINUX)
elseif(WIN32)
    set(TARGET_OS "windows")
    add_definitions(-DTARGET_OS_WINDOWS)
elseif(APPLE)
    set(TARGET_OS "macos")
    add_definitions(-DTARGET_OS_MACOS)
else()
    set(TARGET_OS "unknown")
endif()

# Сообщение после сборки
message(STATUS "ECS_CORE core ${BINARY_NAME} built for ${TARGET_OS}")