#pragma once
#include <string>
#include <iostream>

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
    Book(const Book& other);
    ~Book() = default;

    // Overloading the assignment operator by copying
    Book& operator<<=(const Book& other); // An example of an operator similar to assignment

    // Operator overload
    bool operator==(const Book& other) const;

    // Friendly function (declaration inside the class)
    friend std::ostream& operator<<(std::ostream& os, const Book& book);

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