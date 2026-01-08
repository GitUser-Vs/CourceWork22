#pragma once

#include <string>
#include <iostream>
#include <vector>

class User
{

private:
    // private variables
    int userId;
    std::string name;
    std::string contact;

public:
    // constructors and destructor
    User(int id, std::string n, std::string c);
    User(); // Конструктор по умолчанию

    int getId() const;
    std::string getName() const;
    std::string getContact() const;

    void display() const;

    std::string serialize() const;
    void deserialize(const std::string& data);
};