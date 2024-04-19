#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QString>
#include <vector>
#include <QDir>
#include <QStringList>


// Функция для обработки файла: считывание чисел, запуск потоков для вычисления суммы, разности и XOR
void processFile(const QString& filename, long long& sum, long long& subtraction, long long& xorResult);

// Функция для чтения чисел из файла
std::vector<long long> readNumbersFromFile(const QString& filename);

// Функция для получения пути к файлу от пользователя
QString getFilePath();

// Функция для выбора файла из списка
void chooseFile(QDir& directory, QStringList& txtFiles);

#endif // FILEOPERATIONS_H
