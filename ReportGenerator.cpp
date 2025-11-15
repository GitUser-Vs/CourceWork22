#include "ReportGenerator.hpp"
#include <iostream>

// public methods
void ReportGenerator::generate(const String& reportType) const
{
    // just the output of the message
    std::cout << "  ReportGenerator: Generating '" << reportType << "' report..." << std::endl;

}