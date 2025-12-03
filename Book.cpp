#include "Book.hpp"

// constructors and destructor
Book::Book() : m_BookID(0), m_title("Unknown Title"), m_author("Unknown Author"), m_quantity(0), m_available(0)
{

}

Book::Book(int BookID, const std::string& title, const std::string& author, int quantity)
    : m_BookID(BookID), m_title(title), m_author(author), m_quantity(quantity), m_available(quantity)
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
std::string Book::getTitle() const { return m_title; }
std::string Book::getAuthor() const { return m_author; }
int Book::getQuantity() const { return m_quantity; }
int Book::getAvailable() const { return m_available; }