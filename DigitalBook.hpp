#pragma once
#include "Book.hpp" // Наследование от Book

class DigitalBook : public Book
{
private:
    std::string m_downloadLink;
    int m_fileSizeMB;

public:
    DigitalBook();
    DigitalBook(int bookId, const std::string& title, const std::string& author, int quantity,
        const std::string& link, int fileSize);

    // Деструктор
    ~DigitalBook() override = default;

    // Перегрузка виртуального метода с вызовом метода базового класса
    void displayInfo() const override;

    // Перегрузка метода без вызова базового
    void displayExtendedInfo() const;

    // Реализация клонирования
    LibraryItem* clone() const override;
};

