/*
STUDENT NAME: TILAYA REDDY
STUDENT NUMBER: 402504107
PROGRAMMING 622 ASSIGNMENT
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "EventManager.h"

class FileManager {
public:
    static void writeDefaultConfig(const std::string& filename);
    static void readConfig(const std::string& filename);

    // Exports the full event history to a CSV file that can be opened in
    // Excel or any spreadsheet program.
    static void exportEventsToCSV(const std::string& filename, const std::vector<Event>& history);
};

#endif
