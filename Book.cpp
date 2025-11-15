#include "Book.hpp"

// constructors and destructor
Book::Book() : m_BookID(0), m_title("Unknown Title"), m_author("Unknown Author"), m_quantity(0), m_available(0)
{

}

Book::Book(int BookID, const String& title, const String& author, int quantity)
    : m_BookID(BookID), m_title(title), m_author(author), m_quantity(quantity), m_available(quantity)
{

}

Book::~Book()
{

}

// public methods
void Book::displayInfo() const
{
    std::cout << "Book ID: " << m_BookID
        << ", Title: " << m_title
        << ", Author: " << m_author
        << ", Quantity: " << m_quantity
        << ", Available: " << m_available << std::endl;
}

void Book::decreaseAvailable()
{
    if (m_available > 0) {
        m_available--;
    }
}

void Book::increaseAvailable()
{
    if (m_available < m_quantity) {
        m_available++;
    }
}

// getters
int Book::getBookID() const { return m_BookID; }
String Book::getTitle() const { return m_title; }
String Book::getAuthor() const { return m_author; }
int Book::getQuantity() const { return m_quantity; }
int Book::getAvailable() const { return m_available; }