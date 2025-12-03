#pragma once

#include <string>
#include <iostream>

// forward declaration
class Book;
class User;
class Transaction;

class ReportGenerator
{

public:
    // constructor and destructor
    ReportGenerator() = default;
    ~ReportGenerator() = default;

    // public
    void generate(const std::string& ReportType) const;

};