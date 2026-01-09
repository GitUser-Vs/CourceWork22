#include "Book.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// constructors
Book::Book(int id, string t, string a, string i)
    : bookId(id), title(t), author(a), isbn(i), isAvailable(true) {}

Book::Book() : bookId(0), isAvailable(true) {}

// getters
int Book::getId() const { return bookId; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getIsbn() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }

// setters
void Book::display() const {
    cout << "ID: " << bookId << " | Название: " << title
        << " | Автор: " << author << " | ISBN: " << isbn
        << " | Статус: " << (isAvailable ? "Доступна" : "Выдана") << endl;
}

void Book::setAvailability(bool status) { isAvailable = status; }

string Book::serialize() const {
    return to_string(bookId) + "," + title + "," + author + "," + isbn + "," + (isAvailable ? "1" : "0");
}

void Book::deserialize(const string& data) {
    stringstream ss(data);
    string segment;
    vector<string> seglist;

    while (getline(ss, segment, ',')) {
        seglist.push_back(segment);
    }

    if (seglist.size() == 5) {
        bookId = stoi(seglist[0]);
        title = seglist[1];
        author = seglist[2];
        isbn = seglist[3];
        isAvailable = (seglist[4] == "1");
    }


