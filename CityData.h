/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef CITYDATA_H
#define CITYDATA_H

#include <vector>
#include <list>
#include <string>

// A single day's worth of sensor readings for the city.
struct SensorReading {
    int day;
    double energyUsage;   // in MWh
    int trafficDensity;   // vehicles counted
    int populationCount;
};


class CityData {
private:
    std::vector<SensorReading> readings;
    std::list<std::string> historicalLogs;

public:
    // --- vector operations ---
    void addReading(const SensorReading& reading);       // O(1) amortised
    void removeOldestReading();                          // O(n) - erase(begin())
    void displayReadings() const;                         // O(n) traversal
    const std::vector<SensorReading>& getReadings() const;

    // --- linked list operations ---
    void addLogEntry(const std::string& entry);           // O(1) push_back
    void removeOldestLog();                                // O(1) pop_front
    void displayLogs() const;                              // O(n) traversal
    const std::list<std::string>& getLogs() const;

    // --- persistence ---
    void saveToFile(const std::string& readingsFile, const std::string& logsFile) const;
    void loadFromFile(const std::string& readingsFile, const std::string& logsFile);
};

#endif
