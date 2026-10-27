/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef ANALYTICS_H
#define ANALYTICS_H

#include <vector>
#include "CityData.h"
#include "EventManager.h"

class Analytics {
public:
    // sort() -> O(n log n). Chosen because we need the FULL list of readings
    // arranged in order (ascending energy usage), not just the smallest/
    // largest value, so a full comparison sort is the right tool.
    static std::vector<SensorReading> sortReadingsByEnergyUsage(std::vector<SensorReading> readings);

    // min_element() / max_element() -> both O(n), a single pass through the
    // data. Chosen because we only need ONE extreme value, so a full sort
    // (O(n log n)) would do unnecessary extra work.
    static SensorReading findHighestEnergyUsage(const std::vector<SensorReading>& readings);
    static SensorReading findLowestEnergyUsage(const std::vector<SensorReading>& readings);

    // count_if() -> O(n). Chosen because we must inspect every event once to
    // decide whether it counts as "critical" - there is no way to know
    // without checking each one, so O(n) is the best possible complexity.
    static int countCriticalAlerts(const std::vector<Event>& history, int criticalThresholdSeconds);

    // find() -> O(n) linear search on an UNSORTED vector. Chosen because
    // event history is stored in the order it happened (not sorted by ID),
    // so a linear scan is required to find a specific event by ID.
    static bool findEventByID(const std::vector<Event>& history, int id, Event& foundEvent);

    // --- Section 6 reports (also built using STL algorithms/iterators) ---
    static void printSystemReport(const std::vector<Event>& history);
};

#endif
