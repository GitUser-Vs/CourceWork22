#include "SearchEngine.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

// public methods
vector <Book> SearchEngine::searchByTitle(const vector<Book>& books, const std::string& query) const
{
    vector<Book> results;
    for (const auto& book : books) {
        if (book.getTitle().find(query) != string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

vector <Book> SearchEngine::searchByAuthor(const vector<Book>& books, const std::string& query) const
{
    vector<Book> results;
    for (const auto& book : books) {
        if (book.getAuthor().find(query) != string::npos) {
            results.push_back(book);
        }
    }
    return results;
}