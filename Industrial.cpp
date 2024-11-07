#include "Industrial.h"
#include "Region.h"
#include <iostream>
#include <algorithm>
using namespace std;

Industrial::Industrial(int x, int y, Region* region) : Cell('I', x, y, region) {
    this->population = 0; 
    this->pollution = 0; 
}


void Industrial::grow() {
        int availableWorkers = region->getAvailableWorkers();
        int availableGoods = region->getAvailableGoods();
        
        if (availableGoods == 0){
        if (population == 0 && region->adjToPowerline(x, y) && availableWorkers >= 2) {
            population++;
            region->modifyAvailableWorkers(-2); 
            region->modifyAvailableGoods(1); 
        } else {
            int populatedAdjCells = region->getCountPopulatedAdjCell(x, y);
            
            
            if (population == 0 && populatedAdjCells >= 1 && availableWorkers >= 2) {
                population++;
                region->modifyAvailableWorkers(-2);
                region->modifyAvailableGoods(1); 
            } else if (population == 1 && populatedAdjCells >= 2 && availableWorkers >= 2) {
                population++;
                region->modifyAvailableWorkers(-2);
                region->modifyAvailableGoods(1); 
            } else if (population == 2 && populatedAdjCells >= 4 && availableWorkers >= 2) {
                population++;
                region->modifyAvailableWorkers(-2);
                region->modifyAvailableGoods(1); 
            }
        }
        }
}


void Industrial::spreadPollution() {
    int pollutionAmount = population; 
    vector<Cell*> adjacentCells = region->getAdjacentCells(x, y);
    
    for (Cell* adjCell : adjacentCells) {
        if (adjCell) {
            adjCell->pollution += max(0, pollutionAmount - 1); 
        }
    }
}

