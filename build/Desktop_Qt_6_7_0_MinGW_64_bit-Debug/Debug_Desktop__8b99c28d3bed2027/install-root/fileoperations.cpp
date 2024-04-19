#include "fileoperations.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <stdexcept>
#include <QRegularExpression>
#include <numeric>
#include <QStandardPaths>
#include <thread>

int fileIndex = 0;
// Функция для подсчета суммы всех чисел в векторе
void calculateSum(const std::vector<long long>& numbers, long long& sum) {
    sum = std::accumulate(numbers.begin(), numbers.end(), 0LL);
}
// Функция для вычисления разности первого числа и суммы остальных чисел в векторе
void calculateSubtraction(const std::vector<long long>& numbers, long long firstNumber, long long& subtraction) {
    subtraction = firstNumber - std::accumulate(numbers.begin(), numbers.end(), 0LL);
}
// Функция для вычисления XOR всех чисел в векторе
void calculateXOR(const std::vector<long long>& numbers, long long& xorResult) {
    xorResult = std::accumulate(numbers.begin(), numbers.end(), 0LL, [](long long a, long long b) { return a ^ b; });
}
// Функция для обработки файла: считывание чисел, запуск потоков для вычисления суммы, разности и XOR
void processFile(const QString& filename, long long& sum, long long& subtraction, long long& xorResult) {
    try {
        std::vector<long long> numbers = readNumbersFromFile(filename);
        if (numbers.empty()) {
            std::cerr<<std::endl << "Числа отсутсвуют." << std::endl;
            exit(1);
        }

        long long firstNumber = numbers.front();
        numbers.erase(numbers.begin());
        // Запуск потоков для вычисления суммы, разности и XOR
        std::thread sumThread(calculateSum, std::cref(numbers), std::ref(sum));
        std::thread subtractionThread(calculateSubtraction, std::cref(numbers), firstNumber, std::ref(subtraction));
        std::thread xorThread(calculateXOR, std::cref(numbers), std::ref(xorResult));
        // Ожидание завершения всех потоков
        sumThread.join();
        subtractionThread.join();
        xorThread.join();
    } catch (const std::exception& e) {
        throw e;
    }
}
// Функция для чтения чисел из файла
std::vector<long long> readNumbersFromFile(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Не удалось открыть файл: " << filename.toStdString() << std::endl;
        throw std::runtime_error("Ошибка при открытии файла");
    }

    // Проверка, является ли файл пустым
    if (file.size() == 0) {
        std::cerr << "Файл пустой." << std::endl;
        file.close();
        return std::vector<long long>(); // Возвращаем пустой вектор
    }

    std::vector<long long> numbers;
    QTextStream in(&file);

    static const QRegularExpression regExp("[^0-9\\s]");
    bool invalidCharactersPrinted = false; // Флаг для отслеживания вывода сообщения об ошибке о недопустимых символах

    while (!in.atEnd()) {
        QString numberString = in.readLine();
        if (!numberString.isEmpty()) {
            if (!numberString.contains(regExp)) {
                QStringList parts = numberString.split(" ");
                if (parts.size() >= 6) {
                    for (const QString& part : parts) {
                        if (!part.isEmpty()) {
                            numbers.push_back(part.toLongLong());
                        }
                    }
                } else {
                    std::cerr << "Ошибка: в строке меньше 6 чисел: " << numberString.toStdString() << std::endl;
                }
            } else {
                if (!invalidCharactersPrinted) {
                    std::cerr << "Содержит иные символы:\n" << numberString.toStdString() << std::endl;
                    invalidCharactersPrinted = true; // Установка флага
                }
            }
        }
    }
    file.close();
    return numbers;
}
// Функция для получения пути к файлу от пользователя
QString getFilePath() {
    QDir::setCurrent(QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));

    QDir directory(".");
    QStringList txtFiles = directory.entryList(QStringList() << "*.txt", QDir::Files);

    if (txtFiles.isEmpty()) {
        std::cerr << "Файлы с расширением .txt не найдены в директории загрузки." << std::endl;
        bool validInput = false;
        do {
            std::cout << "Введите путь к директории с файлами .txt или 'exit' для завершения программы: ";
            std::string input;
            std::cin >> input;
            if (input == "exit") {
                exit(1);
            }
            directory.setPath(QString::fromStdString(input));
            txtFiles = directory.entryList(QStringList() << "*.txt", QDir::Files);
            if (txtFiles.isEmpty()) {
                std::cerr << "Файлы с расширением .txt не найдены в указанной директории." << std::endl;
            } else {
                validInput = true;
            }
        } while (!validInput);
    }

    chooseFile(directory, txtFiles);

    if (fileIndex == 0) {
        return QString();
    }

    return directory.filePath(txtFiles[fileIndex - 1]);
}
// Функция для выбора файла из списка
void chooseFile(QDir& directory, QStringList& txtFiles) {
    std::cout << "Выбранная директория: " << directory.absolutePath().toStdString() << std::endl;
    bool validInput = false;
    do {
        std::cout << "Найдены следующие файлы с расширением .txt:" << std::endl;
        for (int i = 0; i < txtFiles.size(); ++i) {
            std::cout << i + 1 << ": " << txtFiles[i].toStdString() << std::endl;
        }
        std::cout << "Выберите файл для обработки или 'exit' для завершения программы: ";
        std::string input;
        std::cin >> input;
        if (input == "exit") {
            exit(1);
        }
        try {
            fileIndex = std::stoi(input);
            if (fileIndex < 1 || fileIndex > txtFiles.size()) {
                throw std::invalid_argument("Некорректный индекс файла.");
            }
            validInput = true;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: введите корректный индекс файла." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Ошибка: введен слишком большой или слишком маленький индекс." << std::endl;
        }
    } while (!validInput);
}
