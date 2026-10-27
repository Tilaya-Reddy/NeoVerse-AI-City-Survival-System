/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef ENGINEER_H
#define ENGINEER_H

#include <string>

class Engineer {
private:
    std::string engineerID;        // e.g. "ENG001"
    std::string username;
    std::string encryptedPassword; // simple encryption, see .cpp for explanation
    std::string clearanceLevel;    // "Low", "Medium" or "High"

public:
    // Constructor - takes a PLAIN TEXT password and encrypts it before storing
    Engineer(std::string id, std::string uname, const std::string& plainPassword, std::string clearance);

    // Factory function used ONLY when loading engineers back from a file,
    // where the password stored on disk is ALREADY encrypted and must not
    // be encrypted a second time.
    static Engineer fromEncryptedRecord(const std::string& id, const std::string& uname,
                                         const std::string& alreadyEncryptedPassword,
                                         const std::string& clearance);

    // Getters (kept const because they do not change the object)
    std::string getID() const;
    std::string getUsername() const;
    std::string getEncryptedPassword() const;
    std::string getClearanceLevel() const;

    // Checks a plain text password entered at login against the stored one
    bool checkPassword(const std::string& plainPassword) const;

    // Encrypts a plain text password using a very simple Caesar-cipher style
    // shift. This is NOT meant to be real-world secure encryption - it is
    // only used to demonstrate the concept of "storing an encrypted password"
    // for this simulation assignment.
    static std::string encryptPassword(const std::string& plainPassword);

    // Used when printing engineer details to the console or to a file
    void display() const;
};

#endif
