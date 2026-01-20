#include "FineCalculator.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

// constructors and destructor
string FineCalculator::getCurrentDateString() const
{
    time_t now = time(0);
    tm t_local;

    localtime_s(&t_local, &now);

    stringstream ss;
    ss << put_time(&t_local, "%Y-%m-%d");
    return ss.str();
}

long FineCalculator::dateToDays(const string& dateStr) const
{
    tm t{};
    stringstream ss(dateStr);
    ss >> get_time(&t, "%Y-%m-%d");

    // Converting time_t to long with explicit cast
    time_t result_time = mktime(&t);
    return static_cast<long>(result_time / (60 * 60 * 24));
}

// public methods
double FineCalculator::calculateFine (const Transaction& t) const
{
	if (!t.isActiveStatus()) {
        return 0.0;
    }
    string todayStr = getCurrentDateString();
    long todayDays = dateToDays(todayStr);
    long dueDays = dateToDays(t.getDueDate());

    if (todayDays > dueDays) {
        int daysOverdue = todayDays - dueDays;
        return (double)daysOverdue * FINE_PER_DAY;
    }
    return 0.0;
}
