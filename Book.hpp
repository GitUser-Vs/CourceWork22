#pragma once
#include <string>
#include <iostream>

// Use "using" to shorten the record, as in the example
using String = std::string;

class Book
{

private:
    // private variables
    int m_BookID;
    String m_title;
    String m_author;
    int m_quantity;
    int m_available;

public:
    // constructors and destructor
    Book();
    Book(int BookID, const String& title, const String& author, int quantity);
    ~Book() = default;

    // public methods
    void displayInfo() const;
    void decreaseAvailable();
    void increaseAvailable();

    // Getters for accessing private fields (for demonstration)
    int getBookID() const;
    String getTitle() const;
    String getAuthor() const;
    int getQuantity() const;
    int getAvailable() const;
};