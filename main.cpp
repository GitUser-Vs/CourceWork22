#include "Library.hpp"
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

std::string activeUser = "";
Role activeRole = Role::USER;
int activeUserId = 0;

void displayMainMenu() {
    cout << "\n====================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ БИБЛИОТЕКОЙ (LMS)" << endl;
    cout << "====================================" << endl;
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
    cout << "11. Посмотреть и открыть выданные книги" << endl;
    cout << "0. Сохранить и Выход" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Введите ваш выбор: ";
}

void displayAuthMenu() {
    cout << "\n--- АВТОРИЗАЦИЯ ---" << endl;
    cout << "1. Войти" << endl;
    cout << "2. Зарегистрироваться" << endl;
    cout << "0. Выход" << endl;
}

void displayAdminMenu() {

}

void displayUserMenu() {
    cout << "\n================" << endl;
    cout << "БИБЛИОТЕКА (LMS)" << endl;
    cout << "================" << endl;
    cout << "1. Выдать книгу" << endl;
    cout << "2. Вернуть книгу" << endl;
    cout << "3. Поиск книг" << endl;
    cout << "4. Показать все книги в библиотеке" << endl;
    cout << "5. Посмотреть и открыть книги в моём распоряжении" << endl;
    cout << "0. Сохранить и Выход" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Введите ваш выбор: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    Library lms;
    int choice;
    bool loggedIn = false;

    while (!loggedIn) {
        displayAuthMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
            cout << "Некорректный ввод. Попробуйте снова." << endl;
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            if (lms.login(activeUser, activeRole, activeUserId)) {
                loggedIn = true;
            }
        }
        else if (choice == 2) {
            lms.registerUser();
        }
        else if (choice == 0) {
            choice = -1; // Выход из цикла
            break;
        }
        else {
            cout << "Неверный выбор." << endl;
        }
    }

    if (loggedIn) {
        cout << "\n--- Привет, " << activeUser << " ---" << endl;
        do {
            
            if (activeRole == Role::ADMIN) {
                displayMainMenu();
            }
            else {
                displayUserMenu();
            }
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                choice = -1;
                cout << "Некорректный ввод. Попробуйте снова." << endl;
                continue;
            }
            cin.ignore(); // Очистка буфера после выбора меню
            
            if (activeRole == Role::ADMIN) {
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
                case 11: lms.addBook(true); break;
                case 0: /*choice = -1;*/
                    // Деструктор Library будет вызван автоматически
                    break;
                default:
                    cout << "Неверный пункт меню." << endl;
                }
            }
            else {
                switch (choice) {
                case 1: lms.borrowBook(); break;
                case 2: lms.returnBook(); break;
                case 3: lms.searchMenu(); break;
                case 4: lms.displayAllBooks(); break;
                case 5: lms.viewMyBooks(activeUserId); break;
                case 0: /*choice = -1;*/ break;
                default: cout << "Неверный пункт меню." << endl;
                }
            }
        } while (choice != 0);
    }
    return 0;
}