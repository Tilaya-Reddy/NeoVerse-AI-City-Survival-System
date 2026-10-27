/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "EventManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

EventManager::EventManager() : nextEventID(1), nextEmergencyID(1) {
}

void EventManager::reportEvent(const std::string& type, const std::string& description) {
    Event e;
    e.eventID = nextEventID++;
    e.type = type;
    e.description = description;
    e.responseTimeSeconds = 5 + (std::rand() % 56);
    eventQueue.push(e); // O(1)
}

bool EventManager::processNextEvent() {
    if (eventQueue.empty()) {
        return false;
    }
    Event e = eventQueue.front();
    eventQueue.pop(); // O(1) - removes from the FRONT, first in, first out
    std::cout << "Processed event #" << e.eventID << " (" << e.type << "): "
              << e.description << " [response time: " << e.responseTimeSeconds << "s]\n";
    processedHistory.push_back(e);
    return true;
}

bool EventManager::hasPendingEvents() const {
    return !eventQueue.empty();
}

void EventManager::displayQueue() const {
    std::queue<Event> copy = eventQueue;
    std::cout << "\n--- Pending Events (queue, front to back) ---\n";
    if (copy.empty()) {
        std::cout << "(no pending events)\n";
    }
    while (!copy.empty()) {
        const Event& e = copy.front();
        std::cout << "#" << e.eventID << " " << e.type << " - " << e.description << "\n";
        copy.pop();
    }
}

void EventManager::raiseEmergency(const std::string& type, const std::string& description) {
    EmergencyEvent e;
    e.eventID = nextEmergencyID++;
    e.type = type;
    e.description = description;
    overrideStack.push(e); // O(1)
}

bool EventManager::resolveTopEmergency() {
    if (overrideStack.empty()) {
        return false;
    }
    EmergencyEvent e = overrideStack.top();
    overrideStack.pop(); // O(1) - removes the MOST RECENTLY added emergency first
    std::cout << "Resolved emergency #" << e.eventID << " (" << e.type << "): "
              << e.description << "\n";
    return true;
}

bool EventManager::hasPendingEmergencies() const {
    return !overrideStack.empty();
}

void EventManager::displayStack() const {
    std::stack<EmergencyEvent> copy = overrideStack;
    std::cout << "\n--- Pending Emergencies (stack, top to bottom) ---\n";
    if (copy.empty()) {
        std::cout << "(no pending emergencies)\n";
    }
    while (!copy.empty()) {
        const EmergencyEvent& e = copy.top();
        std::cout << "#" << e.eventID << " " << e.type << " - " << e.description << "\n";
        copy.pop();
    }
}

const std::vector<Event>& EventManager::getHistory() const {
    return processedHistory;
}

void EventManager::saveHistoryToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) return;
    for (const Event& e : processedHistory) {
        out << e.eventID << "|" << e.type << "|" << e.description << "|"
            << e.responseTimeSeconds << "\n";
    }
}

void EventManager::loadHistoryFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) return;

    processedHistory.clear();
    std::string line;
    int maxID = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string idStr, type, description, respStr;
        std::getline(ss, idStr, '|');
        std::getline(ss, type, '|');
        std::getline(ss, description, '|');
        std::getline(ss, respStr, '|');

        Event e;
        e.eventID = std::stoi(idStr);
        e.type = type;
        e.description = description;
        e.responseTimeSeconds = std::stoi(respStr);
        processedHistory.push_back(e);
        if (e.eventID > maxID) maxID = e.eventID;
    }
    nextEventID = maxID + 1;
}
