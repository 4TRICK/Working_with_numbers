#ifndef PROCESSFILE_H
#define PROCESSFILE_H

#include <iostream>
#include <vector>
#include <QString>

// Функция для обработки файла с указанным номером
void processFile(const QString& filename, const std::vector<unsigned char>& key);

#endif // PROCESSFILE_H
