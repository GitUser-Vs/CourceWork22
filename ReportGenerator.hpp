#pragma once

#include <string>
#include <iostream>

using String = std::string;

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
    void generate(const String& ReportType) const;

};