/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include <vector>
#include <string>
#include "Engineer.h"


class AuthSystem {
private:
    std::vector<Engineer> engineers;

public:
    void addEngineer(const Engineer& engineer);

    // Linear search login: returns true if username + password match an
    // engineer in the vector, and copies that engineer's details into
    // loggedInEngineer.
    bool login(const std::string& username, const std::string& password, Engineer& loggedInEngineer) const;

    // Demonstrates the O(log n) alternative asked about in the brief.
    // Requires the vector to be sorted by username first.
    bool binarySearchLogin(const std::string& username, const std::string& password) const;

    void displayAllEngineers() const;

    const std::vector<Engineer>& getEngineers() const;

    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
};

#endif
