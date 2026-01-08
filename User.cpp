#include "User.hpp"

// constructors and destructor
User::User(int id, string n, string c) : userId(id), name(n), contact(c) {}
User::User() : userId(0) {}

void User::display() const {
    cout << "User ID: " << userId << " | Имя: " << name
        << " | Контакт: " << contact << endl;
}

string User::serialize() const {
    return to_string(userId) + "," + name + "," + contact;
}

void User::deserialize(const string& data) {
    stringstream ss(data);
    string segment;
    vector<string> seglist;
    while (getline(ss, segment, ',')) {
        seglist.push_back(segment);
    }
    if (seglist.size() == 3) {
        userId = stoi(seglist[0]);
        name = seglist[1];
        contact = seglist[2];
    }
}

//getters
int User::getId() const { return userId; }
string User::getName() const { return name; }
string User::getContact() const { return contact; }