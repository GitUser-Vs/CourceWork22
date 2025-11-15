#ifndef SEARCHENGINE_HPP
#define SEARCHENGINE_HPP

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
    SearchEngine();
    ~SearchEngine();

    // public methods
    void searchBooks (const String& query) const;
    void searchUsers(const String& query) const;
};

#endif