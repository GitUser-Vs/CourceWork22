#pragma once

#include <string>
#include <iostream>

class Transaction
{
private:
    // private variables
    int transactionId;
    int bookId;
    int userId;

    std::string borrowDate;
    std::string dueDate;
    std::string returnDate;
    bool isActive;

    std::string getCurrentDate() const;

public:
    Transaction();
    Transaction(int Id, int bookId, int userId);
    ~Transaction() = default;

    // Getters
    int getTransactionId() const;
    int getBookId() const;
    int getUserId() const;
    std::string getDueDate() const;
    bool isActiveStatus() const;

    void completeTransaction();

    void display() const;

    std::string serialize() const;
    void deserialize(const std::string& data);

};