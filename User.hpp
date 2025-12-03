#pragma once

#include <string>
#include <iostream>



class User
{

private:
    // private variables
    int m_UserID;
    std::string m_name;
    std::string m_email;
    int m_borrowedCount;
    int m_maxBorrowedCount;

public:
    // constructors and destructor
    User();
    User(int UserID, const std::string& name, const std::string& email, int maxBorrowedCount);
    ~User() = default;

    // public methods
    void displayInfo() const;
    bool borrowBook();
    bool returnBook();

    // Getters
    int getUserID() const;
    std::string getName() const;
    std::string getEmail() const;
    int getBorrowedCount() const;
    int getMaxBorrowedCount() const;
};