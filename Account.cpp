#include "Account.hpp"
#include <sstream>
#include <vector>

using namespace std;

Account::Account(string user, string pass, Role r, int id)
    : username(user), passwordHash(pass), role(r), associatedId(id) {}

Account::Account() : role(Role::USER), associatedId(0) {}

std::string Account::serialize() const {
    string roleStr = (role == Role::ADMIN) ? "ADMIN" : "USER";
    return username + "," + passwordHash + "," + roleStr + "," + to_string(associatedId);
}

void Account::deserialize(const string& data) {
    stringstream ss(data);
    string segment;
    vector<string> seglist;
    while (getline(ss, segment, ',')) {
        seglist.push_back(segment);
    }

    if (seglist.size() == 4) {
        username = seglist[0];
        passwordHash = seglist[1];
        if (seglist[2] == "ADMIN") {
            role = Role::ADMIN;
        }
        else {
            role = Role::USER;
        }
        associatedId = stoi(seglist[3]);
    }
}