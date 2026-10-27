/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "AuthSystem.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

void AuthSystem::addEngineer(const Engineer& engineer) {
    engineers.push_back(engineer);
}

bool AuthSystem::login(const std::string& username, const std::string& password, Engineer& loggedInEngineer) const {
    auto it = std::find_if(engineers.begin(), engineers.end(),  // performs a LINEAR SEARCH through the vector - O(n).
        [&username](const Engineer& e) {
            return e.getUsername() == username;
        });

    if (it != engineers.end() && it->checkPassword(password)) {
        loggedInEngineer = *it;
        return true;
    }
    return false;
}

bool AuthSystem::binarySearchLogin(const std::string& username, const std::string& password) const {
    std::vector<Engineer> sortedCopy = engineers;
    std::sort(sortedCopy.begin(), sortedCopy.end(),
        [](const Engineer& a, const Engineer& b) {
            return a.getUsername() < b.getUsername();
        });

    // std::lower_bound performs the binary search - O(log n).
    auto it = std::lower_bound(sortedCopy.begin(), sortedCopy.end(), username,
        [](const Engineer& e, const std::string& uname) {
            return e.getUsername() < uname;
        });

    if (it != sortedCopy.end() && it->getUsername() == username) {
        return it->checkPassword(password);
    }
    return false;
}

void AuthSystem::displayAllEngineers() const {
    std::cout << "\n--- Registered Engineers ---\n";
    for (const Engineer& e : engineers) {
        e.display();
    }
}

const std::vector<Engineer>& AuthSystem::getEngineers() const {
    return engineers;
}

void AuthSystem::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error: could not open " << filename << " for writing.\n";
        return;
    }
    for (const Engineer& e : engineers) {
        outFile << e.getID() << "|" << e.getUsername() << "|"
            << e.getEncryptedPassword() << "|" << e.getClearanceLevel() << "\n";
    }
    outFile.close();
}

void AuthSystem::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        // Not an error - the file simply does not exist yet on first run.
        return;
    }

    engineers.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, uname, encPass, clearance;
        std::getline(ss, id, '|');
        std::getline(ss, uname, '|');
        std::getline(ss, encPass, '|');
        std::getline(ss, clearance, '|');
            engineers.push_back(Engineer::fromEncryptedRecord(id, uname, encPass, clearance));
    }
    inFile.close();
}
