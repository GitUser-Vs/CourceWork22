#include "SystemHelper.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool SystemHelper::openFile(const string& path) {
    if (path.empty()) {
        cerr << "Ошибка: Файл книги не указан." << endl;
        return false;
    }

    // --- Cross-platform emulation of file opening ---
#ifdef _WIN32
    // Windows (uses "start" to open the file with the appropriate program.)
    string command = "start \"\" \"" + path + "\"";
#elif __APPLE__
    // macOS
    string command = "open \"" + path + "\"";
#else
    // Linux (uses xdg-open)
    string command = "xdg-open \"" + path + "\"";
#endif

    cout << "Попытка открыть файл: " << path << endl;

    // Executing a command in the OS
    int result = system(command.c_str());

    if (result == 0) {
        cout << "Файл успешно открыт (или команда выполнена)." << endl;
        return true;
    }
    else {
        cerr << "Ошибка при выполнении системной команды. Код: " << result << endl;
        return false;
    }
}