#pragma once

#include <string>
#include <iostream>

// forward declaration
class Book;
class User;

class SearchEngine
{

public:
    // constructor and destructor
    SearchEngine() = default;
    ~SearchEngine() = default;

    // public methods
    void searchBooks (const std::string& query) const;
    void searchUsers(const std::string& query) const;
};