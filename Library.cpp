#include "Library.hpp"
#include "Book.hpp"
#include "User.hpp"

// constructors and destructor
Library::Library()
    : m_name("Unknown Library"), m_address("Unknown Address"),
    m_booksArray(nullptr), m_bookCount(0), m_maxBooks(0),
    m_usersArray(nullptr), m_userCount(0), m_maxUsers(0),
    m_fineCalculator(new FineCalculator()),
    m_searchEngine(new SearchEngine()),
    m_reportGenerator(new ReportGenerator())
{

}

Library::Library(const std::string& name, const std::string& address, int maxBooks, int maxUsers)
    : m_name(name), m_address(address),
    m_bookCount(0), m_maxBooks(maxBooks > 0 ? maxBooks : 100),
    m_userCount(0), m_maxUsers(maxUsers > 0 ? maxUsers : 50),
    m_fineCalculator(new FineCalculator(0.75)), // Example with a parameter for FineCalculator
    m_searchEngine(new SearchEngine()),
    m_reportGenerator(new ReportGenerator())
{
    // Initializing arrays
    m_booksArray = new Book[m_maxBooks];
    m_usersArray = new User[m_maxUsers];
}

Library::~Library()
{
    // Freeing dynamically allocated memory for arrays
    delete[] m_booksArray;
    delete[] m_usersArray;

    // Releasing aggregated objects
    delete m_fineCalculator;
    delete m_searchEngine;
    delete m_reportGenerator;
}

// --- Methods for working with books ---
void Library::addBook(const Book& book)
{
    if (m_bookCount < m_maxBooks) {
        m_booksArray[m_bookCount] = book;
        m_bookCount++;
        std::cout << "Added book to library: '" << book.getTitle() << "'" << std::endl;
    }
    else {
        std::cout << "Library is full. Cannot add more books." << std::endl;
    }
}

void Library::displayBooks() const
{
    std::cout << "\n--- Books in Library ---" << std::endl;
    if (m_bookCount == 0) {
        std::cout << "No books in the library yet." << std::endl;
        return;
    }
    for (int i = 0; i < m_bookCount; ++i) {
        m_booksArray[i].displayInfo();
    }
    std::cout << "------------------------" << std::endl;
}

Book* Library::findBookById(int BookID)
{
    for (int i = 0; i < m_bookCount; ++i) {
        if (m_booksArray[i].getBookID() == BookID) {
            return &m_booksArray[i];
        }
    }
    return nullptr; // Book not found
}

// --- Methods for working with users ---
void Library::addUser(const User& user)
{
    if (m_userCount < m_maxUsers) {
        m_usersArray[m_userCount] = user;
        m_userCount++;
        std::cout << "Added user to library: '" << user.getName() << "'" << std::endl;
    }
    else {
        std::cout << "Library is full. Cannot add more users." << std::endl;
    }
}

void Library::displayUsers() const
{
    std::cout << "\n--- Users in Library ---" << std::endl;
    if (m_userCount == 0) {
        std::cout << "No users in the library yet." << std::endl;
        return;
    }
    for (int i = 0; i < m_userCount; ++i) {
        m_usersArray[i].displayInfo();
    }
    std::cout << "------------------------" << std::endl;
}

User* Library::findUserById(int UserID)
{
    for (int i = 0; i < m_userCount; ++i) {
        if (m_usersArray[i].getUserID() == UserID) {
            return &m_usersArray[i];
        }
    }
    return nullptr; // User not found
}

// --- Methods using aggregated objects ---
void Library::processLending(int BookID, int UserID)
{
    std::cout << "\nProcessing lending for Book ID " << BookID << " to User ID " << UserID << "..." << std::endl;
    Book* book = findBookById(BookID);
    User* user = findUserById(UserID);

    if (!user) {
        std::cout << "Lending failed. User with ID " << UserID << " not found." << std::endl;
        return;
    }
    if (!book) {
        std::cout << "Lending failed. Book with ID " << BookID << " not found." << std::endl;
        return;
    }

    if (user->borrowBook()) {
        book->decreaseAvailable();
        std::cout << "Lending successful. Book '" << book->getTitle() << "' lent to '" << user->getName() << "'." << std::endl;
    }
    else {
        std::cout << "Lending failed. User '" << user->getName() << "' has reached maximum borrowed books." << std::endl;
    }

}

void Library::processReturn(int BookID, int UserID)
{
    std::cout << "\nProcessing return for Book ID " << BookID << " by User ID " << UserID << "..." << std::endl;
    Book* book = findBookById(BookID);
    User* user = findUserById(UserID);

    if (!user) {
        std::cout << "Return failed. User with ID " << UserID << " not found." << std::endl;
        return;
    }
    if (!book) {
        std::cout << "Return failed. Book with ID " << BookID << " not found." << std::endl;
        return;
    }

    if (user->returnBook()) {
        book->increaseAvailable();
        std::cout << "Return successful. Book '" << book->getTitle() << "' returned by '" << user->getName() << "'." << std::endl;
        int daysOverdue = 3;
        double fine = m_fineCalculator->calculateFine(daysOverdue);
        std::cout << "  Fine calculated: $" << fine << std::endl;
    }
    else {
        std::cout << "Return failed. User '" << user->getName() << "' has no books borrowed (or error in tracking)." << std::endl;
    }
}

void Library::performSearch(const std::string& query)
{
    std::cout << "\nPerforming search in Library..." << std::endl;
    m_searchEngine->searchBooks(query);
    m_searchEngine->searchUsers(query); 
}

void Library::generateLibraryReport()
{
    std::cout << "\nGenerating report for Library..." << std::endl;
    m_reportGenerator->generate("Library Overview");
}

void Library::displayLibraryInfo() const
{
    std::cout << "Library Name: " << m_name << ", Address: " << m_address << std::endl;
    std::cout << "Max books capacity: " << m_maxBooks << ", Current books: " << m_bookCount << std::endl;
    std::cout << "Max users capacity: " << m_maxUsers << ", Current users: " << m_userCount << std::endl;
}