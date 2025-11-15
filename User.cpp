#include "User.hpp"

// constructors and destructor
User::User() : m_UserID(0), m_name("Unknown User"), m_email(""), m_borrowedCount(0), m_maxBorrowedCount(0)
{

}

User::User(int UserID, const String& name, const String& email, int maxBorrowedCount)
    : m_UserID(UserID), m_name(name), m_email(email), m_borrowedCount(0), m_maxBorrowedCount(maxBorrowedCount)
{
    
}

// public methods
void User::displayInfo() const
{
    std::cout << "User ID: " << m_UserID
        << ", Name: " << m_name
        << ", Email: " << m_email
        << ", Borrowed: " << m_borrowedCount << "/" << m_maxBorrowedCount << std::endl;
}

bool User::borrowBook()
{
    if (m_borrowedCount < m_maxBorrowedCount) {
        m_borrowedCount++;
        return true;
    }
    return false; // It is impossible to take more books
}

bool User::returnBook()
{
    if (m_borrowedCount > 0) {
        m_borrowedCount--;
        return true;
    }
    return false; // There is nothing to return
}

//getters
int User::getUserID() const { return m_UserID; }
String User::getName() const { return m_name; }
String User::getEmail() const { return m_email; }
int User::getBorrowedCount() const { return m_borrowedCount; }
int User::getMaxBorrowedCount() const { return m_maxBorrowedCount; }