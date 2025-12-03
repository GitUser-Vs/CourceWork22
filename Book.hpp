#pragma once
#include <string>
#include <iostream>
#include <memory> // Äëÿ std::shared_ptr è std::unique_ptr

class Book
{

private:
    // private variables
    int m_BookID;
    std::string m_title;
    std::string m_author;
    int m_quantity;
    int m_available;

public:
    // constructors and destructor
    Book();
    Book(int BookID, const std::string& title, const std::string& author, int quantity);
    ~Book() = default;

    // public methods
    void displayInfo() const;
    void decreaseAvailable();
    void increaseAvailable();

    // Getters for accessing private fields (for demonstration)
    int getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getQuantity() const;
    int getAvailable() const;
};