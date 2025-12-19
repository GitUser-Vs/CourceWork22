#include "DigitalBook.hpp"
#include <iostream>

DigitalBook::DigitalBook()
    : Book(0, "Unknown EBook", "Unknown", 0), m_downloadLink("N/A"), m_fileSizeMB(0) {}

DigitalBook::DigitalBook(int bookId, const std::string& title, const std::string& author, int quantity,
    const std::string& link, int fileSize)
    : Book(bookId, title, author, quantity),
    m_downloadLink(link),
    m_fileSizeMB(fileSize)
{
}

// Перегрузка виртуального метода с вызовом базового
void DigitalBook::displayInfo() const {
    Book::displayInfo();
    std::cout << "[E-BOOK] Link: " << m_downloadLink << ", Size: " << m_fileSizeMB << "MB";
}

// Перегрузка метода без вызова базового
void DigitalBook::displayExtendedInfo() const {
    std::cout << "--- EXTENDED DIGITAL BOOK INFO ---" << std::endl;
    std::cout << "Title: " << m_title << ", Author: " << m_author << std::endl;
    std::cout << "Link: " << m_downloadLink << std::endl;
}

// Реализация клонирования
LibraryItem* DigitalBook::clone() const {
    return new DigitalBook(*this);
}