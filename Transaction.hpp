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
    //double m_fineAmount;

    std::string getCurrentDate() const;

public:
    Transaction();
    Transaction(int Id, int bookId, int userId);
    //Transaction(const Transaction& other);
    ~Transaction() = default;

    // Getters
    int getTransactionId() const;
    int getBookId() const;
    int getUserId() const;
    //const std::tm& getIssueDate() const;
    std::string getDueDate() const;
    //const std::tm& getReturnDate() const;
    bool isActiveStatus() const;
    //double getFineAmount() const;

    void completeTransaction();

    void display() const;

    std::string serialize() const;
    void deserialize(const std::string& data);

};