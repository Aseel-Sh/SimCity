#include "Industrial.h" 
#include "Commercial.h"
#include "Region.h"
#include <iostream>
#include <algorithm> 
#include <queue>
#include <utility> 
#include <vector>
using namespace std;

Industrial::Industrial(int x, int y, Region* region) : Cell('I', x, y, region) {
    this->population = 0; 
    this->pollution = 0; 
}


void Industrial::grow() {
    bool nearPowerline = region->adjToPowerline(x, y);
    int availableWorkers = region->getAvailableWorkers();

   
    if (this->population == 0) {
        int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 0);
        if ((nearPowerline || nearbyPopulatedCells >= 1) && availableWorkers >= 2) {
            this->population++;
            region->modifyAvailableWorkers(-2);
            spreadPollution();
        }
    } else if (this->population == 1) {
        int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 1);
        if (nearbyPopulatedCells >= 2 && availableWorkers >= 2) {
            this->population++;
            region->modifyAvailableWorkers(-2);
            spreadPollution();
        }
    } else if (this->population == 2) {
        int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 2);
        if (nearbyPopulatedCells >= 4 && availableWorkers >= 2) {
            this->population++;
            region->modifyAvailableWorkers(-2);
            spreadPollution();
        }
    } else if (this->population == 3) {
        int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 3);
        if (nearbyPopulatedCells >= 6 && availableWorkers >= 2) {
            this->population++;
            region->modifyAvailableWorkers(-2);
            spreadPollution();
        }
    } else if (this->population == 4) {
        int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 4);
        if (nearbyPopulatedCells >= 8 && availableWorkers >= 2) {
            this->population++;
            region->modifyAvailableWorkers(-2);
            spreadPollution();
        }
    } 

    region->modifyAvailableGoods(this->population);

} 





void Industrial::spreadPollution() {
    int maxPollution = this->population;
    if (maxPollution <= 0) return;

    int rows = region->getRows();
    int cols = region->getCols();

    
    const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, 
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    
    queue<pair<int, int>> cellQueue;
    queue<int> pollutionQueue;

   
    cellQueue.push(make_pair(x, y));
    pollutionQueue.push(maxPollution);

    while (!cellQueue.empty()) {
        
        pair<int, int> current = cellQueue.front();
        cellQueue.pop();
        int currentX = current.first;
        int currentY = current.second;

        
        int currentPollution = pollutionQueue.front();
        pollutionQueue.pop();

        
        Cell* cell = region->getCell(currentX, currentY);
        if (cell != nullptr && cell->pollution < currentPollution) {
            cell->pollution = currentPollution;
        }

       
        if (currentPollution > 1) {
            for (int i = 0; i < 8; i++) {
                int newX = currentX + directions[i][0];
                int newY = currentY + directions[i][1];

              
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    Cell* neighborCell = region->getCell(newX, newY);
                    if (neighborCell != nullptr && neighborCell->pollution < currentPollution - 1) {
                        
                        cellQueue.push(make_pair(newX, newY));
                        pollutionQueue.push(currentPollution - 1);
                    }
                }
            }
        }
    }
}