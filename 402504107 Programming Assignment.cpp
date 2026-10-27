/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "Engineer.h"
#include "AuthSystem.h"
#include "CityData.h"
#include "EventManager.h"
#include "CityComponent.h"
#include "CitySystems.h"
#include "Analytics.h"
#include "FileManager.h"


const std::string ENGINEERS_FILE = "data/engineers.dat";
const std::string READINGS_FILE = "data/city_readings.dat";
const std::string LOGS_FILE = "data/city_logs.dat";
const std::string EVENTS_FILE = "data/events.dat";
const std::string CONFIG_FILE = "data/config.txt";
const std::string EVENTS_CSV_FILE = "data/events_export.csv";

// Clears a bad std::cin state after invalid menu input.
void clearInputError() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void seedDemoEngineersIfNeeded(AuthSystem& auth) {
    if (!auth.getEngineers().empty()) {
        return; // already loaded from file
    }
    auth.addEngineer(Engineer("ENG001", "M_Reddy", "223874", "High"));
    auth.addEngineer(Engineer("ENG002", "KB_Reddy", "730145", "Medium"));
    auth.addEngineer(Engineer("ENG003", "T_Reddy", "554865", "Low"));
    auth.saveToFile(ENGINEERS_FILE);
}

// Handles the login screen. Returns true if login succeeded.
bool loginScreen(const AuthSystem& auth, Engineer& loggedInEngineer) {
    std::string username, password;
    std::cout << "\n===== NeoVerse AI City Survival System =====\n";
    std::cout << "Please log in to continue.\n";
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    if (auth.login(username, password, loggedInEngineer)) {
        std::cout << "\nLogin successful. Welcome, " << loggedInEngineer.getUsername()
            << " (Clearance: " << loggedInEngineer.getClearanceLevel() << ")\n";
        return true;
    }
    std::cout << "\nLogin failed: incorrect username or password.\n";
    return false;
}

void printMainMenu() {
    std::cout << "\n================= MAIN MENU =================\n";
    std::cout << "1.  Report a new city event\n";
    std::cout << "2.  Process next event in queue (FIFO)\n";
    std::cout << "3.  Raise an emergency override\n";
    std::cout << "4.  Resolve top emergency (LIFO)\n";
    std::cout << "5.  View event queue and emergency stack\n";
    std::cout << "6.  Add a sensor reading\n";
    std::cout << "7.  View sensor readings and historical logs\n";
    std::cout << "8.  Run city components (polymorphism demo)\n";
    std::cout << "9.  Run analytics (sort / find / min / max / count)\n";
    std::cout << "10. View system report\n";
    std::cout << "11. View config.txt\n";
    std::cout << "12. Export events to CSV\n";
    std::cout << "13. View registered engineers\n";
    std::cout << "0.  Save and exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    AuthSystem auth;
    auth.loadFromFile(ENGINEERS_FILE);
    seedDemoEngineersIfNeeded(auth);

    CityData cityData;
    cityData.loadFromFile(READINGS_FILE, LOGS_FILE);

    EventManager eventManager;
    eventManager.loadHistoryFromFile(EVENTS_FILE);

    FileManager::writeDefaultConfig(CONFIG_FILE);

    // ---- Login ----
    Engineer loggedInEngineer("", "", "", "");
    bool loggedIn = false;
    int attempts = 0;
    while (!loggedIn && attempts < 3) {
        loggedIn = loginScreen(auth, loggedInEngineer);
        attempts++;
    }
    if (!loggedIn) {
        std::cout << "\nToo many failed attempts. Shutting down.\n";
        return 0;
    }


    std::vector<CityComponent*> cityComponents;
    cityComponents.push_back(new PowerSystem(1, "Central Power Grid", 80.0));
    cityComponents.push_back(new TransportSystem(2, "Downtown Traffic Control", 120));
    cityComponents.push_back(new HealthSystem(3, "Metro Health Network", 4));
    cityComponents.push_back(new SecuritySystem(4, "City Watch", 2));
    for (CityComponent* comp : cityComponents) {
        comp->activate();
    }

    // ---- Main menu loop ----
    bool running = true;
    while (running) {
        printMainMenu();
        int choice;
        std::cin >> choice;
        if (std::cin.fail()) {
            clearInputError();
            std::cout << "Invalid input, please enter a number from the menu.\n";
            continue;
        }
        clearInputError();

        switch (choice) {
        case 1: {
            std::string type, description;
            std::cout << "Event type (e.g. Traffic Accident, Power Failure, Network Overload, Weather Alert): ";
            std::getline(std::cin, type);
            std::cout << "Description: ";
            std::getline(std::cin, description);
            eventManager.reportEvent(type, description);
            cityData.addLogEntry("Event reported: " + type + " - " + description);
            std::cout << "Event added to the queue.\n";
            break;
        }
        case 2: {
            if (!eventManager.processNextEvent()) {
                std::cout << "No events waiting in the queue.\n";
            }
            break;
        }
        case 3: {
            std::string type, description;
            std::cout << "Emergency type: ";
            std::getline(std::cin, type);
            std::cout << "Description: ";
            std::getline(std::cin, description);
            eventManager.raiseEmergency(type, description);
            cityData.addLogEntry("EMERGENCY raised: " + type + " - " + description);
            std::cout << "Emergency pushed onto the override stack.\n";
            break;
        }
        case 4: {
            if (!eventManager.resolveTopEmergency()) {
                std::cout << "No emergencies waiting on the stack.\n";
            }
            break;
        }
        case 5: {
            eventManager.displayQueue();
            eventManager.displayStack();
            break;
        }
        case 6: {
            SensorReading r;
            r.day = static_cast<int>(cityData.getReadings().size()) + 1;
            std::cout << "Energy usage (MWh): ";
            std::cin >> r.energyUsage;
            std::cout << "Traffic density (vehicles): ";
            std::cin >> r.trafficDensity;
            std::cout << "Population count: ";
            std::cin >> r.populationCount;
            clearInputError();
            cityData.addReading(r);
            std::cout << "Sensor reading added.\n";
            break;
        }
        case 7: {
            cityData.displayReadings();
            cityData.displayLogs();
            break;
        }
        case 8: {
            std::cout << "\n--- Running processEvent() on every city component ---\n";
            std::cout << "(Notice: the SAME function call runs DIFFERENT code for\n";
            std::cout << " each object - this is runtime polymorphism.)\n\n";
            for (CityComponent* comp : cityComponents) {
                std::cout << comp->getName() << " [" << comp->getStatus() << "]: ";
                comp->processEvent("Routine city-wide system check");
            }
            break;
        }
        case 9: {
            const std::vector<SensorReading>& readings = cityData.getReadings();
            if (readings.empty()) {
                std::cout << "No sensor readings yet - add some first (option 6).\n";
                break;
            }
            std::vector<SensorReading> sorted = Analytics::sortReadingsByEnergyUsage(readings);
            std::cout << "\nReadings sorted by energy usage (ascending):\n";
            for (const SensorReading& r : sorted) {
                std::cout << "Day " << r.day << ": " << r.energyUsage << " MWh\n";
            }

            SensorReading highest = Analytics::findHighestEnergyUsage(readings);
            SensorReading lowest = Analytics::findLowestEnergyUsage(readings);
            std::cout << "Highest energy usage: Day " << highest.day << " (" << highest.energyUsage << " MWh)\n";
            std::cout << "Lowest energy usage:  Day " << lowest.day << " (" << lowest.energyUsage << " MWh)\n";

            int criticalCount = Analytics::countCriticalAlerts(eventManager.getHistory(), 40);
            std::cout << "Critical alerts (response time >= 40s): " << criticalCount << "\n";

            if (!eventManager.getHistory().empty()) {
                int searchID;
                std::cout << "Enter an event ID to search for (from processed events): ";
                std::cin >> searchID;
                clearInputError();
                Event found;
                if (Analytics::findEventByID(eventManager.getHistory(), searchID, found)) {
                    std::cout << "Found event #" << found.eventID << ": " << found.type
                        << " - " << found.description << "\n";
                }
                else {
                    std::cout << "No processed event with that ID was found.\n";
                }
            }
            break;
        }
        case 10: {
            Analytics::printSystemReport(eventManager.getHistory());
            break;
        }
        case 11: {
            FileManager::readConfig(CONFIG_FILE);
            break;
        }
        case 12: {
            FileManager::exportEventsToCSV(EVENTS_CSV_FILE, eventManager.getHistory());
            break;
        }
        case 13: {
            auth.displayAllEngineers();
            break;
        }
        case 0: {
            running = false;
            break;
        }
        default:
            std::cout << "Please enter a number between 0 and 13.\n";
        }
    }

    std::cout << "\nSaving system state...\n";
    auth.saveToFile(ENGINEERS_FILE);
    cityData.saveToFile(READINGS_FILE, LOGS_FILE);
    eventManager.saveHistoryToFile(EVENTS_FILE);

    for (CityComponent* comp : cityComponents) {
        comp->deactivate();
        delete comp; // triggers each derived destructor, then the base destructor
    }
    cityComponents.clear();

    std::cout << "All data saved. Goodbye!\n";
    return 0;
}
