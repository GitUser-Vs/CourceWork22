#pragma once

#include <string>
#include <iostream>

using String = std::string;

class User
{

private:
    // private variables
    int m_UserID;
    String m_name;
    String m_email;
    int m_borrowedCount;
    int m_maxBorrowedCount;

public:
    // constructors and destructor
    User();
    User(int UserID, const String& name, const String& email, int maxBorrowedCount);
    ~User() = default;

    // public methods
    void displayInfo() const;
    bool borrowBook();
    bool returnBook();

    // Getters
    int getUserID() const;
    String getName() const;
    String getEmail() const;
    int getBorrowedCount() const;
    int getMaxBorrowedCount() const;
};