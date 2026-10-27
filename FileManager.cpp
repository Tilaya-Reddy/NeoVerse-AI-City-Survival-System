/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#include "FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::writeDefaultConfig(const std::string& filename) {
    
    std::ifstream test(filename);
    if (test.good()) {
        return;
    }

    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error: could not create " << filename << "\n";
        return;
    }
    out << "city_name=NeoVerse\n";
    out << "max_engineers=50\n";
    out << "critical_response_threshold_seconds=40\n";
    out << "simulation_speed=1\n";
    out.close();
}

void FileManager::readConfig(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cout << "No config.txt found.\n";
        return;
    }

    std::cout << "\n--- config.txt ---\n";
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            std::cout << line << "\n";
        }
    }
}

void FileManager::exportEventsToCSV(const std::string& filename, const std::vector<Event>& history) {
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error: could not create " << filename << "\n";
        return;
    }

    out << "EventID,Type,Description,ResponseTimeSeconds\n";
    for (const Event& e : history) {
        out << e.eventID << ",\"" << e.type << "\",\"" << e.description << "\","
            << e.responseTimeSeconds << "\n";
    }
    std::cout << "Exported " << history.size() << " events to " << filename << "\n";
}
