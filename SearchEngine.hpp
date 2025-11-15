#pragma once

#include <string>
#include <iostream>

using String = std::string; // type alias

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
    void searchBooks (const String& query) const;
    void searchUsers(const String& query) const;
};