#pragma once
#include <string>

enum class Role { USER, ADMIN };

class Account
{
private:
    std::string username;
    std::string passwordHash;
    Role role;
    int associatedId; // ID User или 0 для чистого админа

public:
    Account(std::string user, std::string pass, Role r, int id = 0);
    Account();

    std::string getUsername() const { return username; }
    std::string getPassword() const { return passwordHash; }
    Role getRole() const { return role; }
    int getAssociatedId() const { return associatedId; }

    std::string serialize() const;
    void deserialize(const std::string& data);
};

