#include "Analytics.h"
#include <algorithm>
#include <iostream>
#include <map>

std::vector<SensorReading> Analytics::sortReadingsByEnergyUsage(std::vector<SensorReading> readings) {
    // std::sort - O(n log n) average and worst case (it is IntroSort in most
    // implementations: quicksort + heapsort fallback + insertion sort for
    // small ranges).
    std::sort(readings.begin(), readings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.energyUsage < b.energyUsage;
        });
    return readings;
}

SensorReading Analytics::findHighestEnergyUsage(const std::vector<SensorReading>& readings) {
    // std::max_element - O(n), single linear pass keeping track of the
    // largest value seen so far.
    auto it = std::max_element(readings.begin(), readings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.energyUsage < b.energyUsage;
        });
    return *it;
}

SensorReading Analytics::findLowestEnergyUsage(const std::vector<SensorReading>& readings) {
    // std::min_element - O(n), single linear pass keeping track of the
    // smallest value seen so far.
    auto it = std::min_element(readings.begin(), readings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.energyUsage < b.energyUsage;
        });
    return *it;
}

int Analytics::countCriticalAlerts(const std::vector<Event>& history, int criticalThresholdSeconds) {
    // std::count_if - O(n), visits every element exactly once and applies
    // the predicate (response time above the critical threshold).
    return static_cast<int>(std::count_if(history.begin(), history.end(),
        [criticalThresholdSeconds](const Event& e) {
            return e.responseTimeSeconds >= criticalThresholdSeconds;
        }));
}

bool Analytics::findEventByID(const std::vector<Event>& history, int id, Event& foundEvent) {
    // std::find_if - O(n) worst case, since the vector is not sorted by ID.
    auto it = std::find_if(history.begin(), history.end(),
        [id](const Event& e) {
            return e.eventID == id;
        });
    if (it != history.end()) {
        foundEvent = *it;
        return true;
    }
    return false;
}

void Analytics::printSystemReport(const std::vector<Event>& history) {
    std::cout << "\n===== SYSTEM REPORT =====\n";
    std::cout << "Total events processed: " << history.size() << "\n";

    if (history.empty()) {
        std::cout << "No events processed yet - report has nothing further to show.\n";
        return;
    }

    std::map<std::string, int> typeCounts;
    long totalResponseTime = 0;

    for (const Event& e : history) {
        typeCounts[e.type]++;
        totalResponseTime += e.responseTimeSeconds;
    }

    std::string mostCommonType;
    int highestCount = 0;
    // Explicit iterator usage, as required in Section 6.
    for (std::map<std::string, int>::iterator it = typeCounts.begin(); it != typeCounts.end(); ++it) {
        if (it->second > highestCount) {
            highestCount = it->second;
            mostCommonType = it->first;
        }
    }

    double averageResponseTime = static_cast<double>(totalResponseTime) / history.size();

    std::cout << "Most common event type: " << mostCommonType
        << " (" << highestCount << " occurrences)\n";
    std::cout << "Average response time: " << averageResponseTime << " seconds\n";
    std::cout << "System load summary: " << history.size() << " total events across "
        << typeCounts.size() << " distinct event types.\n";
    std::cout << "=========================\n";
}
