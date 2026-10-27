/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "CityComponent.h"
#include <iostream>

CityComponent::CityComponent(int id, std::string componentName)
    : componentID(id), name(std::move(componentName)), active(false) {
    std::cout << "[Constructor] CityComponent \"" << name << "\" created.\n";
}

CityComponent::~CityComponent() {
    std::cout << "[Destructor] CityComponent \"" << name << "\" destroyed.\n";
}

void CityComponent::activate() {
    active = true;
}

void CityComponent::deactivate() {
    active = false;
}

std::string CityComponent::getStatus() const {
    return active ? "ACTIVE" : "INACTIVE";
}

int CityComponent::getID() const {
    return componentID;
}

std::string CityComponent::getName() const {
    return name;
}

bool CityComponent::isActive() const {
    return active;
}
