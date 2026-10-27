/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef CITYCOMPONENT_H
#define CITYCOMPONENT_H

#include <string>

class CityComponent {
private:
    int componentID;
    std::string name;
    bool active;

public:
    CityComponent(int id, std::string componentName);

    // Virtual destructor - REQUIRED whenever a base class will be deleted
    // through a base class pointer, so the derived class's destructor also
    // runs and cleans up properly.
    virtual ~CityComponent();

    void activate();
    void deactivate();
    std::string getStatus() const;

    int getID() const;
    std::string getName() const;
    bool isActive() const;

    // Pure virtual function ("= 0") - this makes CityComponent an ABSTRACT
    // class that can never be instantiated directly. Every derived class
    // MUST override this with its own behaviour.
    virtual void processEvent(const std::string& eventDescription) = 0;
};

#endif
