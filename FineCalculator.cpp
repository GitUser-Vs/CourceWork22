#include "FineCalculator.hpp"
#include <iostream>

// constructors and destructor
FineCalculator::FineCalculator() : m_finePerDay(0.5) // Default value
{

}

FineCalculator::FineCalculator(double finePerDay) : m_finePerDay(finePerDay > 0 ? finePerDay : 0.5)
{

}

// public methods
double FineCalculator::calculateFine(int daysOverdue) const
{
	return  (daysOverdue > 0) ? (daysOverdue * m_finePerDay) : 0.0;
}

// Getter
double FineCalculator::getFinePerDay() const { return m_finePerDay; }