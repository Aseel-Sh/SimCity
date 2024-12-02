#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Reads in the config file and gives the simulation its parameters (Region layout, Time limit, and Refresh Rate)
void Config::loadConfig(const std::string& fileName) {
    std::ifstream configFile(fileName);
    if (!configFile.is_open()) {
        std::cerr << "Error opening Config file." << '\n';
        return;
    }

    // String to store each line
    std::string line;
    while (std::getline(configFile, line)) {
        // string stream breaks down the line into letters to parse and filter out what you need
        std::istringstream ss(line);
        // key and value: Key is everything before the colon and the value is after the colon
        std::string key, value;
        std::getline(ss, key, ':');
        std::getline(ss, value);

        value.erase(value.find_last_not_of(" \t\r\n") + 1);


        if (key == "Region Layout") {
            regionFile = value;
        }

        if (key == "Time Limit") {
            // Needed to convert the string value to a integer using stoi
            timeLimit = std::stoi(value);
        }

        if (key == "Refresh Rate") {
            // Again needed to convert string -> int
            refreshRate = std::stoi(value);
        }
    }
}