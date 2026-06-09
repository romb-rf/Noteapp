add_executable(test_noteapp
    main.cpp
    test_note.cpp
    test_tst.cpp   # и другие существующие файлы
)

target_link_libraries(test_noteapp PRIVATE
    GTest::gtest
    GTest::gtest_main
    notecore
    Qt6::Core
    Qt6::Gui

)

# windeployqt (опционально)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt ...)
if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET test_noteapp POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
            --no-translations
            --no-plugins
            --no-system-d3d-compiler
            $<TARGET_FILE:test_noteapp>
        COMMENT "Deploying Qt DLLs for tests..."
    )
endif()

include(GoogleTest)
gtest_discover_tests(test_noteapp)