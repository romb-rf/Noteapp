#include <gtest/gtest.h>
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv); // необходим для работы с файлами и сигналами (таймеры)
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}