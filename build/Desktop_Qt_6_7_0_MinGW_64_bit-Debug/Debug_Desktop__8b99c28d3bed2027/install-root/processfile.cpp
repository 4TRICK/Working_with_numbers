#include "processfile.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

void processFile(const QString& filename, const std::vector<unsigned char>& key) {
    // Открытие файла для чтения в бинарном режиме
    QFile inputFile(filename);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        std::cerr << "Невозможно открыть файл: " << filename.toStdString() << std::endl;
        return;
    }

    // Чтение содержимого файла
    QByteArray buffer = inputFile.readAll();

    // Применение ключа к каждому байту из файла
    for (int i = 0; i < buffer.size(); ++i) {
        buffer[i] ^= key[i % key.size()];
    }

    // Вычисление суммы преобразованных байтов
    unsigned int sum = 0;
    for (char value : buffer) {
        sum += static_cast<unsigned char>(value);
    }

    // Вывод суммы XOR-значений на экран
    std::cout << "Сумма XOR-значений: " << sum << std::endl;
}
