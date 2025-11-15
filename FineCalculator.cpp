#include "FineCalculator.hpp"
#include <iostream>

// constructors and destructor
FineCalculator::FineCalculator() : m_finePerDay(0.5) // Default value
{

}

FineCalculator::FineCalculator(double finePerDay) : m_finePerDay(finePerDay > 0 ? finePerDay : 0.5)
{

}

FineCalculator::~FineCalculator()
{

}

// public methods
double FineCalculator::calculateFine(int daysOverdue) const
{
    if (daysOverdue > 0) {
        return daysOverdue * m_finePerDay;
    }
    return 0.0; // There is no penalty if there is no delay
}

// Getter
double FineCalculator::getFinePerDay() const { return m_finePerDay; }