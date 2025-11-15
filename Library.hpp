#pragma once

#include "FineCalculator.hpp"
#include "SearchEngine.hpp"
#include "ReportGenerator.hpp"
#include <string>
#include <iostream>

// Forward declarations for Book and User
class Book;
class User;

using String = std::string;

class Library
{
public:
    // static const int MAX_BOOKS = 1000;
    // static const int MAX_USERS = 500;

private:
    // private variables
    String m_name;
    String m_address;

    Book* m_booksArray;
    int m_bookCount;
    int m_maxBooks;

    User* m_usersArray;
    int m_userCount;
    int m_maxUsers;

    FineCalculator* m_fineCalculator;
    SearchEngine* m_searchEngine;
    ReportGenerator* m_reportGenerator;

public:
    // constructors and destructor
    Library();
    Library(const String& name, const String& address, int maxBooks, int maxUsers);
    ~Library();

    // public methods
    void displayLibraryInfo() const;

    // methods for working with books
    void addBook(const Book& book);
    void displayBooks() const;
    Book* findBookById(int BookID);

    // methods for working with users
    void addUser(const User& user);
    void displayUsers() const;
    User* findUserById(int UserID); // ¬озвращает указатель на пользовател€

    // methods using aggregated objects
    void processLending(int BookID, int UserID);
    void processReturn(int BookID, int UserID);
    void performSearch(const String& query);
    void generateLibraryReport();

};