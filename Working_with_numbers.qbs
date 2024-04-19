import qbs

CppApplication {
    consoleApplication: true
    targetName: "FileModifier" // Имя целевого исполняемого файла
    qbs.install: true // Установка исполняемого файла после компиляции
    files: [
        "fileoperations.cpp",
        "fileoperations.h",
        "main.cpp",
    ] // Файлы для компиляции
    cpp.includePaths: ["."] // Пути для поиска заголовочных файлов

    Depends { name: "Qt.core" } // Зависимость от модуля Qt Core
    Depends { name: "Qt.widgets" } // Зависимость от модуля Qt Widgets (если нужно)
}
