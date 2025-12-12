#include "Transaction.hpp"
#include <iostream>
#include <iomanip>

// Constructor
Transaction::Transaction()
    : m_transactionId(0), m_bookId(0), m_userId(0), m_isReturned(false), m_fineAmount(0.0)
{
    std::memset(&m_issueDate, 0, sizeof(std::tm));
    std::memset(&m_dueDate, 0, sizeof(std::tm));
    std::memset(&m_returnDate, 0, sizeof(std::tm));
}

// Constructor with parameters
Transaction::Transaction(int transactionId, int bookId, int userId, const std::tm& issueDate, const std::tm& dueDate)
    : m_transactionId(transactionId), m_bookId(bookId), m_userId(userId),
    m_issueDate(issueDate), m_dueDate(dueDate),
    m_isReturned(false), m_fineAmount(0.0)
{
    std::memset(&m_returnDate, 0, sizeof(std::tm));
}

// Copy constructor
Transaction::Transaction(const Transaction& other)
    : m_transactionId(other.m_transactionId),
    m_bookId(other.m_bookId),
    m_userId(other.m_userId),
    m_issueDate(other.m_issueDate),
    m_dueDate(other.m_dueDate),
    m_returnDate(other.m_returnDate),
    m_isReturned(other.m_isReturned),
    m_fineAmount(other.m_fineAmount)
{
    
}

// --- Operator overload ---

// Overloading the assignment operator by copying
Transaction& Transaction::operator=(const Transaction& other)
{
    if (this != &other) // Checking for self-sealing
    {
        m_transactionId = other.m_transactionId;
        m_bookId = other.m_bookId;
        m_userId = other.m_userId;
        m_issueDate = other.m_issueDate;
        m_dueDate = other.m_dueDate;
        m_returnDate = other.m_returnDate;
        m_isReturned = other.m_isReturned;
        m_fineAmount = other.m_fineAmount;
    }
    return *this;
}


// --- Public methods ---
void Transaction::displayInfo() const
{
    std::cout << *this << std::endl;
}

void Transaction::markAsReturned(const std::tm& returnDate, double fine)
{
    m_returnDate = returnDate;
    m_fineAmount = fine;
    m_isReturned = true;
}

// --- Getters ---
int Transaction::getTransactionId() const { return m_transactionId; }
int Transaction::getBookId() const { return m_bookId; }
int Transaction::getUserId() const { return m_userId; }
const std::tm& Transaction::getIssueDate() const { return m_issueDate; }
const std::tm& Transaction::getDueDate() const { return m_dueDate; }
const std::tm& Transaction::getReturnDate() const { return m_returnDate; }
bool Transaction::isReturned() const { return m_isReturned; }
double Transaction::getFineAmount() const { return m_fineAmount; }

// --- Перегрузка оператора << ---
std::ostream& operator<<(std::ostream& os, const Transaction& transaction)
{
    char issueBuf[100];
    char dueBuf[100];
    char returnBuf[100];

    std::strftime(issueBuf, sizeof(issueBuf), "%Y-%m-%d", &transaction.m_issueDate);
    std::strftime(dueBuf, sizeof(dueBuf), "%Y-%m-%d", &transaction.m_dueDate);

    os << "Transaction(ID: " << transaction.m_transactionId
        << ", BookID: " << transaction.m_bookId
        << ", UserID: " << transaction.m_userId
        << ", Issued: " << issueBuf
        << ", Due: " << dueBuf;

    if (transaction.m_isReturned) {
        std::strftime(returnBuf, sizeof(returnBuf), "%Y-%m-%d", &transaction.m_returnDate);
        os << ", Returned: " << returnBuf << ", Fine: $" << transaction.m_fineAmount;
    }
    else {
        os << ", Status: Outstanding";
    }
    os << ")";
    return os;
}