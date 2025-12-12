#pragma once

#include <string>
#include <iostream>
#include <vector>

class User
{

private:
    // private variables
    int m_userId;
    std::string m_name;
    std::string m_email;
    std::vector<int> m_borrowedBookIds;
    int m_maxBorrowedCount;

public:
    // constructors and destructor
    User();
    User(int UserID, const std::string& name, const std::string& email, int maxBorrowedCount);
    User(const User& other); // Copy Constructor
    ~User() = default;

    // Overloading the assignment operator by copying
    User& operator=(const User& other);

    // Friendly functions
    friend std::ostream& operator<<(std::ostream& os, const User& user);

    // public methods
    void displayInfo() const;
    bool borrowBook(int bookId);
    bool returnBook(int bookId);

    // Getters
    int getUserID() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    size_t getBorrowedCount() const;
    int getMaxBorrowedCount() const;

    // Перегрузка оператора для сравнения пользователей по ID
    bool operator==(const User& other) const;
};

// Friendly feature for the operator
std::ostream& operator<<(std::ostream& os, const User& user);