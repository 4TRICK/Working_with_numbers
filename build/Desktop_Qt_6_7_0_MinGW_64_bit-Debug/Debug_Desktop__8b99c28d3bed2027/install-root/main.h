#ifndef MAIN_H
#define MAIN_H
#include <QString>
#include <string>
#include <vector>

// Функция для чтения чисел из файла в вектор
std::vector<int> readNumbersFromFile(const QString& filename);

// Функция для работы с числами в несколько потоков
class NumberProcessor {
public:
    NumberProcessor(int number);
    void run();
    int getResult() const;

private:
    int number;
    int result;
};

#endif // MAIN_H
