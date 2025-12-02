cmake_minimum_required(VERSION 3.16)
project(MyCodeEditor)

# Определяем ОС и режим компиляции
if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling for Windows")
    set(BUILD_FOR_WINDOWS TRUE)
elseif(MINGW OR WIN32)
    message(STATUS "Native Windows build")
    set(BUILD_FOR_WINDOWS TRUE)
else()
    message(STATUS "Native Linux build")
    set(BUILD_FOR_WINDOWS FALSE)
endif()

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматизация Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Поиск Qt
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/syntaxhighlighter.cpp
)

set(HEADERS
    src/mainwindow.h
    src/syntaxhighlighter.h
)

# Создание исполняемого файла
add_executable(MyCodeEditor ${SOURCES} ${HEADERS})

# ВСЕ библиотеки в ОДНОМ вызове target_link_libraries
target_link_libraries(MyCodeEditor
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

# Windows-specific настройки
if(BUILD_FOR_WINDOWS)
    message(STATUS "Applying Windows-specific settings")

    # Для кросскомпиляции используем статическую линковку
    if(CMAKE_CROSSCOMPILING OR MINGW)
        message(STATUS "Static linking for MinGW/Cross-compile")

        # Статическая линковка runtime
        target_link_options(MyCodeEditor PRIVATE
            -static
            -static-libgcc
            -static-libstdc++
        )

        # Дополнительные библиотеки через target_link_options
        target_link_options(MyCodeEditor PRIVATE
            -lpcre2-16
            -lharfbuzz
            -lfreetype
            -lbz2
            -lz
            -lpng16
            -lzstd
            -lwinspool
            -lshlwapi
            -lws2_32
            -ldnsapi
            -liphlpapi
            -luser32
            -lgdi32
            -ladvapi32
            -lole32
            -loleaut32
            -luuid
            -lcomdlg32
            -lcomctl32
            -limm32
            -lwinmm
            -lnetapi32
            -luserenv
        )
    endif()

    # Убираем консольное окно для Windows
    target_link_options(MyCodeEditor PRIVATE -mwindows)

    # Суффикс .exe для Windows
    set_target_properties(MyCodeEditor PROPERTIES SUFFIX ".exe")
endif()

target_include_directories(MyCodeEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Предупреждения компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MyCodeEditor PRIVATE -Wall -Wextra)
endif()
