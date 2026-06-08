cmake_minimum_required(VERSION 3.16)
project(NoteApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(NoteApp
    main.cpp
    note.h note.cpp
    notemanager.h notemanager.cpp
    qml/main.qml qml/NoteDelegate.qml qml/NoteEditPage.qml qml/NotesListPage.qml
)

target_link_libraries(NoteApp PRIVATE Qt6::Quick)

# Копируем папку qml в каталог сборки, чтобы приложение могло найти QML-файлы
add_custom_command(TARGET NoteApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/qml"
    "$<TARGET_FILE_DIR:NoteApp>/qml"
)