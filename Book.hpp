#pragma once
#include <string>
#include <iostream>
#include "LibraryItem.hpp"

class Book : public LibraryItem
{

protected:
    // private variables
    std::string m_author;
    int m_available;

public:
    // constructors and destructor
    Book();
    Book(int BookID, const std::string& title, const std::string& author, int quantity);
    // Конструктор копирования
    Book(const Book& other);
    ~Book() override = default;

    // Оператор присваивания копированием
    Book& operator=(const Book& other);

    // Перегрузка присваивания
    Book& operator=(const LibraryItem& other);

    // public methods
    void displayInfo() const override;
    // Перегрузка метода без вызова базового
    void displayExtendedInfo() const;
    void decreaseAvailable();
    void increaseAvailable();

    // Getters for accessing private fields
    std::string getAuthor() const;
    int getQuantity() const override;
    int getAvailable() const;

    // Реализация клонирования
    LibraryItem* clone() const override;

    // Демонстрация доступа к protected члену базового класса
    void checkProtectedAccess() const;
};
// Перегрузка оператора <<
std::ostream& operator<<(std::ostream& os, const Book& book);