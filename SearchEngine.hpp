#pragma once

#include "Book.hpp"
#include <vector>
#include <string>
#include <iostream>


class SearchEngine
{

public:
    // constructor and destructor
    SearchEngine() = default;
    ~SearchEngine() = default;

    // public methods
    void searchBooks (const std::string& query) const;
    void searchUsers(const std::string& query) const;

    std::vector<Book> searchByTitle(const std::vector<Book>& books, const std::string& query) const;
    std::vector<Book> searchByAuthor(const std::vector<Book>& books, const std::string& query) const;
};