/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "Engineer.h"
#include <iostream>

std::string Engineer::encryptPassword(const std::string& plainPassword) {
    std::string encrypted = plainPassword;
    for (char& c : encrypted) {
        c = static_cast<char>(c + 3);
    }
    return encrypted;
}

Engineer::Engineer(std::string id, std::string uname, const std::string& plainPassword, std::string clearance)
    : engineerID(std::move(id)),
      username(std::move(uname)),
      encryptedPassword(encryptPassword(plainPassword)),
      clearanceLevel(std::move(clearance)) {
}

Engineer Engineer::fromEncryptedRecord(const std::string& id, const std::string& uname,
                                        const std::string& alreadyEncryptedPassword,
                                        const std::string& clearance) {

    Engineer e(id, uname, "", clearance);
    e.encryptedPassword = alreadyEncryptedPassword;
    return e;
}

std::string Engineer::getID() const {
    return engineerID;
}

std::string Engineer::getUsername() const {
    return username;
}

std::string Engineer::getEncryptedPassword() const {
    return encryptedPassword;
}

std::string Engineer::getClearanceLevel() const {
    return clearanceLevel;
}

bool Engineer::checkPassword(const std::string& plainPassword) const {
    return encryptPassword(plainPassword) == encryptedPassword;
}

void Engineer::display() const {
    std::cout << "ID: " << engineerID
              << " | Username: " << username
              << " | Clearance: " << clearanceLevel
              << std::endl;
}
