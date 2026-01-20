#pragma once

#include <string>

class SystemHelper
{
public:
    // Try to open a file using the system command
    static bool openFile(const std::string& path);
};

