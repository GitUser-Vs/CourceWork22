#pragma once

#include <iostream>

class FineCalculator
{
private:
    // private variables
    double m_finePerDay;

public:
    // constructors and destructor
    FineCalculator();
    FineCalculator(double finePerDay);
    ~FineCalculator() = default;

    // public methods
    double calculateFine(int daysOverdue) const;

    // getter (if required)
    double getFinePerDay() const;
};