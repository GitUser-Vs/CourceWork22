#ifndef FINECALCULATOR_HPP
#define FINECALCULATOR_HPP

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
    ~FineCalculator();

    // public methods
    double calculateFine(int daysOverdue) const;

    // getter (if required)
    double getFinePerDay() const;
};

#endif