#pragma once
#include <string>
#include <iostream>

class Book {

private:
    // private variables
    int bookId;
    std::string title;
    std::string author;
    std::string isbn;
    bool isAvailable;
    friend class Library;

public:
    // constructors
    Book();
    Book(int id, std::string t, std::string a, std::string i);

    // public methods
    void display() const;
    std::string serialize() const;
    void deserialize(const std::string& data);

    void setAvailability(bool status);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getIsbn() const;
    bool getAvailability() const;
};