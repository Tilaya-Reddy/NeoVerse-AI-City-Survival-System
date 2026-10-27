/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef CITYSYSTEMS_H
#define CITYSYSTEMS_H

#include "CityComponent.h"

class PowerSystem : public CityComponent {
private:
    double powerLevel; // percentage, 0-100

public:
    PowerSystem(int id, const std::string& name, double startingPowerLevel);
    ~PowerSystem() override;

    void supplyPower(double amount);
    double getPowerLevel() const;

    void processEvent(const std::string& eventDescription) override;
};

class TransportSystem : public CityComponent {
private:
    int trafficFlow; // vehicles per minute

public:
    TransportSystem(int id, const std::string& name, int startingTrafficFlow);
    ~TransportSystem() override;

    void manageTraffic(int adjustment);
    int getTrafficFlow() const;

    void processEvent(const std::string& eventDescription) override;
};

class HealthSystem : public CityComponent {
private:
    int hospitalCnt;

public:
    HealthSystem(int id, const std::string& name, int startingHospitalCount);
    ~HealthSystem() override;

    void provideCare();
    int getHospitalCount() const;

    void processEvent(const std::string& eventDescription) override;
};

class SecuritySystem : public CityComponent {
private:
    int threatLevel; // 0 (safe) - 10 (critical)

public:
    SecuritySystem(int id, const std::string& name, int startingThreatLevel);
    ~SecuritySystem() override;

    void monitorCity();
    int getThreatLevel() const;

    void processEvent(const std::string& eventDescription) override;
};

#endif
