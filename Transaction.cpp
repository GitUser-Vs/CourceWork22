#include "Transaction.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

string Transaction::getCurrentDate() const {
    time_t now = time(0);
    tm t_local;

    localtime_s(&t_local, &now);

    stringstream ss;
    ss << put_time(&t_local, "%Y-%m-%d");
    return ss.str();
}

// Constructor
Transaction::Transaction()
    : transactionId(0), bookId(0), userId(0), isActive(false)
{
}

// Constructor with parameters
Transaction::Transaction(int Id, int bookId, int userId)
    : transactionId(Id), bookId(bookId), userId(userId), isActive(true)
{
    borrowDate = getCurrentDate();

    // The return period is 14 days.
    time_t now = time(0);
    now += 14 * 24 * 60 * 60;
    tm t_due;

    // Secure time acquisition for DueDate
    localtime_s(&t_due, &now);

    stringstream ss;
    ss << put_time(&t_due, "%Y-%m-%d");
    dueDate = ss.str();

    returnDate = "N/A";
}

// --- Public methods ---
void Transaction::display() const
{
    cout << "TID: " << transactionId << " | BookID: " << bookId
        << " | UserID: " << userId << " | Выдана: " << borrowDate
        << " | Срок: " << dueDate << " | Статус: "
        << (isActive ? "Активна" : "Возвращена") << endl;
}

void Transaction::completeTransaction()
{
    isActive = false;
    returnDate = getCurrentDate();
}

// --- Getters ---
int Transaction::getTransactionId() const { return transactionId; }
int Transaction::getBookId() const { return bookId; }
int Transaction::getUserId() const { return userId; }
string Transaction::getDueDate() const { return dueDate; }
bool Transaction::isActiveStatus() const { return isActive; }

string Transaction::serialize() const {
    return to_string(transactionId) + "," + to_string(bookId) + "," + to_string(userId) + "," +
        borrowDate + "," + dueDate + "," + returnDate + "," + (isActive ? "1" : "0");
}

void Transaction::deserialize(const string& data) {
    stringstream ss(data);
    string segment;
    vector<string> seglist;
    while (getline(ss, segment, ',')) {
        seglist.push_back(segment);
    }
    if (seglist.size() == 7) {
        transactionId = stoi(seglist[0]);
        bookId = stoi(seglist[1]);
        userId = stoi(seglist[2]);
        borrowDate = seglist[3];
        dueDate = seglist[4];
        returnDate = seglist[5];
        isActive = (seglist[6] == "1");
    }
}