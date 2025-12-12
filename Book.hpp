#pragma once
#include <string>
#include <iostream>

class Book
{

private:
    // private variables
    int m_bookId;
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

    // Оператор присваивания копированием
    Book& operator=(const Book& other);

    // public methods
    void displayInfo() const;
    void decreaseAvailable();
    void increaseAvailable();

    // Getters for accessing private fields
    int getBookID() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getQuantity() const;
    int getAvailable() const;

    // Дружественная функция для вывода информации
    friend void displayBookDetails(const Book& book);

    // Перегрузка оператора для удобного вывода объекта Book
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};