#include "SearchEngine.hpp"
#include <iostream>

// public methods
void SearchEngine::searchBooks(const String& query) const
{
    // just the output of the message
    std::cout << "  SearchEngine: Searching for books matching '" << query << "'..." << std::endl;

}

void SearchEngine::searchUsers(const String& query) const
{
    // just the output of the message
    std::cout << "  SearchEngine: Searching for users matching '" << query << "'..." << std::endl;

}