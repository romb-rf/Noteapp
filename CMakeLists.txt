cmake_minimum_required(VERSION 3.16)

project(NoteApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Загрузка Google Test ---
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

# --- 2. Поиск Qt ---
find_package(Qt6 REQUIRED COMPONENTS Core Quick Widgets)
qt_standard_project_setup(REQUIRES 6.8)

# --- 3. Статическая библиотека с ядром (логика без GUI) ---
# Содержит классы Note и NoteManager, а также вспомогательные модули
add_library(notecore STATIC
    note.cpp
    notemanager.cpp
    # добавьте другие .cpp файлы, если есть (например, jsonstorage.cpp)
)
target_include_directories(notecore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(notecore PUBLIC Qt6::Core Qt6::Gui)

# --- 4. Основное приложение (GUI) ---
qt_add_executable(NoteApp
    main.cpp
    # другие файлы с виджетами / визуализацией (если есть)
)

qt_add_qml_module(NoteApp
    URI NoteApp
    QML_FILES
        qml/main.qml
        # другие qml-файлы
    SOURCES
        note.h
        notemanager.h
        # дополнительные заголовочные файлы
)

target_link_libraries(NoteApp PRIVATE
    notecore
    Qt6::Quick
    Qt6::Widgets
    Qt6::QuickControls2   # ← добавить эту строку
)

# --- 5. Копирование Qt DLL и плагинов ---
find_program(WINDEPLOYQT_EXECUTABLE windeployqt
    HINTS "${QT6_INSTALL_PREFIX}/bin"
)
if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET NoteApp POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
            $<TARGET_FILE:NoteApp>
            --qmldir "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Deploying Qt dependencies for NoteApp..."
    )
endif()

# Настройки платформы
set_target_properties(NoteApp PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# --- 6. Поддержка тестов ---
enable_testing()

# --- 7. Установка ---
include(GNUInstallDirs)
install(TARGETS NoteApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests_bin)
add_subdirectory(tests)