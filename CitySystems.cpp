/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "CitySystems.h"
#include <iostream>

// ---------------------------- PowerSystem -----------------------------
PowerSystem::PowerSystem(int id, const std::string& name, double startingPowerLevel)
    : CityComponent(id, name), powerLevel(startingPowerLevel) {
}

PowerSystem::~PowerSystem() {

}

void PowerSystem::supplyPower(double amount) {
    powerLevel += amount;
    if (powerLevel > 100) powerLevel = 100;
}

double PowerSystem::getPowerLevel() const {
    return powerLevel;
}

void PowerSystem::processEvent(const std::string& eventDescription) {
    std::cout << "[PowerSystem] Handling event: " << eventDescription
              << " -> reducing power level to simulate load, current level: ";
    powerLevel -= 5;
    if (powerLevel < 0) powerLevel = 0;
    std::cout << powerLevel << "%\n";
}

// -------------------------- TransportSystem ---------------------------
TransportSystem::TransportSystem(int id, const std::string& name, int startingTrafficFlow)
    : CityComponent(id, name), trafficFlow(startingTrafficFlow) {
}

TransportSystem::~TransportSystem() {
}

void TransportSystem::manageTraffic(int adjustment) {
    trafficFlow += adjustment;
    if (trafficFlow < 0) trafficFlow = 0;
}

int TransportSystem::getTrafficFlow() const {
    return trafficFlow;
}

void TransportSystem::processEvent(const std::string& eventDescription) {
    std::cout << "[TransportSystem] Handling event: " << eventDescription
              << " -> rerouting traffic, flow increased to ";
    trafficFlow += 20;
    std::cout << trafficFlow << " vehicles/min\n";
}

// --------------------------- HealthSystem -----------------------------
HealthSystem::HealthSystem(int id, const std::string& name, int startingHospitalCount)
    : CityComponent(id, name), hospitalCnt(startingHospitalCount) {
}

HealthSystem::~HealthSystem() {
}

void HealthSystem::provideCare() {
    // Placeholder for future patient-handling logic.
}

int HealthSystem::getHospitalCount() const {
    return hospitalCnt;
}

void HealthSystem::processEvent(const std::string& eventDescription) {
    std::cout << "[HealthSystem] Handling event: " << eventDescription
              << " -> dispatching emergency medical response using "
              << hospitalCnt << " hospital(s)\n";
}

// -------------------------- SecuritySystem -----------------------------
SecuritySystem::SecuritySystem(int id, const std::string& name, int startingThreatLevel)
    : CityComponent(id, name), threatLevel(startingThreatLevel) {
}

SecuritySystem::~SecuritySystem() {
}

void SecuritySystem::monitorCity() {
    // Placeholder for future surveillance logic.
}

int SecuritySystem::getThreatLevel() const {
    return threatLevel;
}

void SecuritySystem::processEvent(const std::string& eventDescription) {
    std::cout << "[SecuritySystem] Handling event: " << eventDescription
              << " -> raising threat level to ";
    threatLevel += 1;
    if (threatLevel > 10) threatLevel = 10;
    std::cout << threatLevel << "/10\n";
}
