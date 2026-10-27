/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "CityData.h"
#include <iostream>
#include <fstream>
#include <sstream>

void CityData::addReading(const SensorReading& reading) {
    readings.push_back(reading); // O(1) amortised
}

void CityData::removeOldestReading() {
    if (!readings.empty()) {
        readings.erase(readings.begin()); // O(n) - every remaining element shifts left
    }
}

void CityData::displayReadings() const {
    std::cout << "\n--- Sensor Readings (vector) ---\n";
    for (const SensorReading& r : readings) {
        std::cout << "Day " << r.day
                  << " | Energy: " << r.energyUsage << " MWh"
                  << " | Traffic: " << r.trafficDensity
                  << " | Population: " << r.populationCount << "\n";
    }
}

const std::vector<SensorReading>& CityData::getReadings() const {
    return readings;
}

void CityData::addLogEntry(const std::string& entry) {
    historicalLogs.push_back(entry); // O(1)
}

void CityData::removeOldestLog() {
    if (!historicalLogs.empty()) {
        historicalLogs.pop_front(); // O(1) - no shifting needed in a linked list
    }
}

void CityData::displayLogs() const {
    std::cout << "\n--- Historical City Logs (linked list) ---\n";
    for (const std::string& log : historicalLogs) {
        std::cout << log << "\n";
    }
}

const std::list<std::string>& CityData::getLogs() const {
    return historicalLogs;
}

void CityData::saveToFile(const std::string& readingsFile, const std::string& logsFile) const {
    std::ofstream readingsOut(readingsFile);
    if (readingsOut) {
        for (const SensorReading& r : readings) {
            readingsOut << r.day << "|" << r.energyUsage << "|"
                        << r.trafficDensity << "|" << r.populationCount << "\n";
        }
    }

    std::ofstream logsOut(logsFile);
    if (logsOut) {
        for (const std::string& log : historicalLogs) {
            logsOut << log << "\n";
        }
    }
}

void CityData::loadFromFile(const std::string& readingsFile, const std::string& logsFile) {
    std::ifstream readingsIn(readingsFile);
    if (readingsIn) {
        readings.clear();
        std::string line;
        while (std::getline(readingsIn, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string dayStr, energyStr, trafficStr, popStr;
            std::getline(ss, dayStr, '|');
            std::getline(ss, energyStr, '|');
            std::getline(ss, trafficStr, '|');
            std::getline(ss, popStr, '|');

            SensorReading r;
            r.day = std::stoi(dayStr);
            r.energyUsage = std::stod(energyStr);
            r.trafficDensity = std::stoi(trafficStr);
            r.populationCount = std::stoi(popStr);
            readings.push_back(r);
        }
    }

    std::ifstream logsIn(logsFile);
    if (logsIn) {
        historicalLogs.clear();
        std::string line;
        while (std::getline(logsIn, line)) {
            if (!line.empty()) {
                historicalLogs.push_back(line);
            }
        }
    }
}
