#ifndef REPORTGENERATOR_HPP
#define REPORTGENERATOR_HPP

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
    ReportGenerator();
    ~ReportGenerator();

    // public
    void generate(const String& ReportType) const;

};
#endif