#include "Config.h"
#include "Region.h"
#include <iostream>

int main() {

    std::string configFileName; // Variable to store config file name
    std::cout << "Please provide the config file name: ";
    std::getline(std::cin, configFileName);

    // Loads the config from the config1 file and then out puts the data
    Config config;
    config.loadConfig(configFileName);

    std::cout << "Region layout: " << config.regionFile << '\n';
    std::cout << "Time Limit: " << config.timeLimit << '\n';
    std::cout << "Refresh Rate: " << config.refreshRate << '\n';

    // start up the region based on the rows and columns
    int rows = 0, cols = 0;
    Region::getRegionSize(config.regionFile, rows, cols);

    if (rows == 0 || cols == 0) {
        std::cerr << "Did not find region size from file." << '\n';
        return 1;
    }

    // Initilizes the region using the parsed rows and cols
    Region region(rows, cols);

    // Loads the initial region layout from the region 1 file
    region.loadRegion(config.regionFile);
    std::vector<std::vector<Cell*>> clonedGrid = region.cloneGrid(); //Clone initial grid for SelectArea()

    std::cout << "Initial region state Time step 0:" << '\n';
    region.printRegion();

    //run the simulation using the time limit and refresh rate from the configuration
    region.runSim(config.timeLimit, config.refreshRate);

    //dispay metrics
    region.printTotalPopulations();
    region.printRegionPollution();

    //user-defined selection and analysis of an area in the cloned grid (bonus)
    region.selectArea(clonedGrid, config.timeLimit, config.refreshRate);

    return 0;
}