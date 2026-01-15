#include "Library.hpp"
#include <iostream>
#include <vector>

using namespace std;

void displayMainMenu() {
    cout << "\n===================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ БИБЛИОТЕКОЙ (LMS)" << endl;
    cout << "===================================" << endl;
    cout << "УПРАВЛЕНИЕ РЕСУРСАМИ:" << endl;
    cout << "1. Добавить книгу" << endl;
    cout << "2. Добавить пользователя" << endl;
    cout << "3. Изменить/Обновить книгу" << endl;
    cout << "ВЫДАЧА/ВОЗВРАТ:" << endl;
    cout << "4. Выдать книгу" << endl;
    cout << "5. Вернуть книгу" << endl;
    cout << "ОТЧЕТЫ И ПОИСК:" << endl;
    cout << "6. Поиск книг" << endl;
    cout << "7. Сгенерировать отчеты" << endl;
    cout << "ОБЩИЕ:" << endl;
    cout << "8. Показать все книги" << endl;
    cout << "9. Показать всех пользователей" << endl;
    cout << "10. Показать историю транзакций" << endl;
    cout << "0. Сохранить и Выход" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Введите ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    Library lms;
    int choice;

    do {
        displayMainMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            cout << "Некорректный ввод. Попробуйте снова." << endl;
            continue;
        }
        cin.ignore(); // Очистка буфера после выбора меню

        switch (choice) {
        case 1: lms.addBook(); break;
        case 2: lms.addUser(); break;
        case 3: lms.updateBook(); break;
        case 4: lms.borrowBook(); break;
        case 5: lms.returnBook(); break;
        case 6: lms.searchMenu(); break;
        case 7: lms.generateReports(); break;
        case 8: lms.displayAllBooks(); break;
        case 9: lms.displayAllUsers(); break;
        case 10: lms.displayAllTransactions(); break;
        case 0:
            // Деструктор Library будет вызван автоматически
            break;
        default:
            cout << "Неверный пункт меню." << endl;
        }
    } while (choice != 0);

    return 0;
}