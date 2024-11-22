#include <iostream>

#include "Residential.h"


Residential::Residential(int x, int y, Region* region) : Cell('R', x, y, region) {} // Default Constructor

Residential* Residential::clone() const {
        return new Residential(*this);
}

void Residential::grow() {
    int population;
    bool nearPowerline = region->adjToPowerline(x,y); // funct. to check adj to powerline for initial population growth
    int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,population); // funct. to check popuated cells 
    int availableWorkers = region->getAvailableWorkers(); // a way where I can update available workers based on poplation

    if (this->population == 0) {
    nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,0);
        if (nearPowerline || nearbyPopulatedCells >= 1) { // If cell is near a powerline or nearbypopulatedcells >= 2
            this->population++; // increment population
            availableWorkers++; // increment availableWorkers
            region->modifyAvailableWorkers(+1);
        }
    }
    else if (this->population == 1) {
        nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,1);
        if (nearbyPopulatedCells >= 2) {
            this->population++;
            availableWorkers++;
            region->modifyAvailableWorkers(+1);
        }
    }
    else if (this->population == 2) {
        nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,2);
        if (nearbyPopulatedCells >= 4) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
        }
    }
    else if (this->population == 3) {
        nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,3);
        if (nearbyPopulatedCells >= 6) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
        }
    }
    else if (this->population == 4) {
        nearbyPopulatedCells = region->getCountPopulatedAdjCell(x,y,4);
        if (nearbyPopulatedCells >= 8) {
        this->population++;
        availableWorkers++;
        region->modifyAvailableWorkers(+1);
        }
    }
}