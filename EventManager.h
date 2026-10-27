/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <queue>
#include <stack>
#include <vector>
#include <string>

// A normal, non-urgent city event (traffic accident, power failure, etc.)
struct Event {
    int eventID;
    std::string type;        // e.g. "Traffic Accident", "Power Failure"
    std::string description;
    int responseTimeSeconds; // used later for the average response time report
};

// A high-priority emergency that must interrupt normal processing.
struct EmergencyEvent {
    int eventID;
    std::string type;
    std::string description;
};

class EventManager {
private:
    std::queue<Event> eventQueue;
    std::stack<EmergencyEvent> overrideStack;

    // Keeps a full history of everything ever processed, so we can run
    // reports (Section 6) and STL algorithms (Section 5) over it afterwards.
    std::vector<Event> processedHistory;

    int nextEventID;
    int nextEmergencyID;

public:
    EventManager();

    // --- queue (FIFO) operations ---
    void reportEvent(const std::string& type, const std::string& description);
    bool processNextEvent();          // pops the front of the queue
    bool hasPendingEvents() const;
    void displayQueue() const;

    // --- stack (LIFO) operations ---
    void raiseEmergency(const std::string& type, const std::string& description);
    bool resolveTopEmergency();       // pops the top of the stack
    bool hasPendingEmergencies() const;
    void displayStack() const;

    // --- history, used by Analytics & Reports ---
    const std::vector<Event>& getHistory() const;

    // --- persistence ---
    void saveHistoryToFile(const std::string& filename) const;
    void loadHistoryFromFile(const std::string& filename);
};

#endif
