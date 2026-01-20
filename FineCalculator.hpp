#pragma once

#include "Transaction.hpp"
#include <iostream>

class FineCalculator
{
private:
    // private variables
    const int FINE_PER_DAY = 5;
    std::string getCurrentDateString() const;
    long dateToDays(const std::string& dateStr) const;

public:
    // public methods
    double calculateFine(const Transaction& t) const;
};