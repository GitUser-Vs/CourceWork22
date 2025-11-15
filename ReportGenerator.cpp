#include "ReportGenerator.hpp"
#include <iostream>

// constructor and destructor
ReportGenerator::ReportGenerator()
{

}

ReportGenerator::~ReportGenerator()
{

}

// public methods
void ReportGenerator::generate(const String& reportType) const
{
    // just the output of the message
    std::cout << "  ReportGenerator: Generating '" << reportType << "' report..." << std::endl;

}