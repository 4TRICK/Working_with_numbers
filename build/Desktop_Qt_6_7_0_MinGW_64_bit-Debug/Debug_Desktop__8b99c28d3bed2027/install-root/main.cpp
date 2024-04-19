#include <iostream>
#include <windows.h>
#include <clocale>
#include <thread>
#include <QString>
#include "fileoperations.h"

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleOutputCP(65001);

    long long sum, subtraction, xorResult;
    try {
        QString filePath = getFilePath();
        if (filePath.isEmpty()) {
            return 0;
        }
        processFile(filePath, sum, subtraction, xorResult);
        std::cout << "\tСумма чисел: " << sum << std::endl;
        std::cout << "\tРезультат вычитания: " << subtraction << std::endl;
        std::cout << "\tXOR всех чисел: " << xorResult << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}


