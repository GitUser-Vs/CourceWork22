#pragma once

#include <string>
#include <iostream>

class Transaction
{
private:
    // private variables
    int m_transactionId;
    int m_bookId;
    int m_userId;

    std::tm m_issueDate;
    std::tm m_dueDate;
    std::tm m_returnDate;
    bool m_isReturned;
    double m_fineAmount;

public:
    Transaction();
    Transaction(int transactionId, int bookId, int userId, const std::tm& issueDate, const std::tm& dueDate);
    Transaction(const Transaction& other);
    ~Transaction() = default;

    // Overloading the assignment operator by copying
    Transaction& operator=(const Transaction& other);

    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

    // Public methods
    void displayInfo() const;
    void markAsReturned(const std::tm& returnDate, double fine);

    // Getters
    int getTransactionId() const;
    int getBookId() const;
    int getUserId() const;
    const std::tm& getIssueDate() const;
    const std::tm& getDueDate() const;
    const std::tm& getReturnDate() const;
    bool isReturned() const;
    double getFineAmount() const;

};

// Перегрузка оператора для вывода объекта Transaction
std::ostream& operator<<(std::ostream& os, const Transaction& transaction);