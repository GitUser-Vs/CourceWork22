#include "ReportGenerator.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// public methods
void ReportGenerator::generateActiveLoansReport(const std::vector<Transaction>& transactions,
    const vector<User>& users,
    const vector<Book>& books) const
{
    cout << "\n--- ОТЧЕТ ОБ АКТИВНЫХ ВЫДАЧАХ ---" << endl;
    bool found = false;
    for (const auto& t : transactions) {
        if (t.isActiveStatus()) {
            found = true;
            cout << "Транзакция ID: " << t.getTransactionId() << endl;

            // User search
            auto userIt = find_if(users.begin(), users.end(),
                [t](const User& u) { return u.getId() == t.getUserId(); });

            if (userIt != users.end()) {
                cout << "  Пользователь: " << userIt->getName() << " (ID: " << t.getUserId() << ")" << endl;
            }
            else {
                cout << "  Пользователь: ID " << t.getUserId() << " (Не найден)" << endl;
            }

            // Book search
            auto bookIt = find_if(books.begin(), books.end(),
                [t](const Book& b) { return b.getId() == t.getBookId(); });

            if (bookIt != books.end()) {
                cout << "  Книга: " << bookIt->getTitle() << " (ID: " << t.getBookId() << ")" << endl;
                cout << "  Срок возврата: " << t.getDueDate() << endl;
            }
            else {
                cout << "  Книга: ID " << t.getBookId() << " (Не найдена)" << endl;
            }
            cout << "-----------------------------------" << endl;
        }
    }
    if (!found) {
        cout << "Активных выданных книг нет." << endl;
    }
}