#pragma once

#include "Transaction.hpp"
#include "User.hpp"
#include "Book.hpp"
#include <vector>
#include <string>
#include <iostream>

class ReportGenerator
{

public:
    // constructor and destructor
    ReportGenerator() = default;
    ~ReportGenerator() = default;

    // public
    void generateActiveLoansReport(const std::vector<Transaction>& transactions, const std::vector<User>& users,
        const std::vector<Book>& books) const;

};