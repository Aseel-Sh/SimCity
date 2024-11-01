#include <iostream>

#include "Residential.h"


Residential::Residential(int x, int y, Region* region) : Cell('R', x, y, region) {} // Default Constructor

void Residential::grow() {
    bool nearPowerline = region->adjToPowerline(x,y); // funct. to check adj to powerline for initial population growth
    int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y); // funct. to check popuated cells 
    int availableWorkers = region->getAvailableWorkers(); // a way where I can update available workers based on poplation

    if (this->population == 0) {
        if (nearPowerline || nearbyPopulatedCells >= 1) { // If cell is near a powerline or nearbypopulatedcells >= 2
            this->population++; // increment population
            availableWorkers++; // increment availableWorkers
            region->modifyAvailableWorkers(+1);
        }
    }
    else if (this->population == 1 && nearbyPopulatedCells >= 2) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
    }
    else if (this->population == 2 && nearbyPopulatedCells >= 4) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
    }
    else if (this->population == 3 && nearbyPopulatedCells >= 6) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
    }
    else if (this->population == 4 && nearbyPopulatedCells >= 8) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
    }
}