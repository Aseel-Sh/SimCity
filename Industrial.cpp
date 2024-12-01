#include "Industrial.h" 
#include "Commercial.h"
#include "Region.h"
#include <iostream>
#include <algorithm> 
#include <queue>
#include <utility> 
#include <vector>
using namespace std; 

// Constructor for Industrial cell

Industrial::Industrial(int x, int y, Region* region) : Cell('I', x, y, region) {
    this->population = 0; 
    this->pollution = 0; 
}

Industrial* Industrial::clone() const {
        return new Industrial(*this);
} 

// Grow function for the Industrial zone

void Industrial::grow() {
    bool nearPowerline = region->adjToPowerline(x, y);
    int availableWorkers = region->getAvailableWorkers();

    // Increase population if conditions are met
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

// Generate goods based on population
    region->modifyAvailableGoods(this->population);

} 




// Spread pollution function
void Industrial::spreadPollution() {
    int maxPollution = this->population;
    if (maxPollution <= 0) return;

    int rows = region->getRows();
    int cols = region->getCols();

     // Directions for 8 neighboring cells (including diagonals)
    const int directions[8][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, 
        {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
    };

    
    // Use explicit types for the queue elements
    queue<pair<int, int>> cellQueue;
    queue<int> pollutionQueue;

   
    // Add the initial cell to the queue
    cellQueue.push(make_pair(x, y));
    pollutionQueue.push(maxPollution);

    while (!cellQueue.empty()) {
        // Get the current cell coordinates from the queue
        pair<int, int> current = cellQueue.front();
        cellQueue.pop();
        int currentX = current.first;
        int currentY = current.second;

         // Get the current pollution level from the queue
        int currentPollution = pollutionQueue.front();
        pollutionQueue.pop();

        
        Cell* cell = region->getCell(currentX, currentY);
        if (cell != nullptr && cell->pollution < currentPollution) {
            cell->pollution = currentPollution;
        }

        // Spread pollution to neighboring cells if the pollution level is greater than 1
        if (currentPollution > 1) {
            for (int i = 0; i < 8; i++) {
                int newX = currentX + directions[i][0];
                int newY = currentY + directions[i][1];

               // Check if new coordinates are within grid bounds
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    Cell* neighborCell = region->getCell(newX, newY);
                    if (neighborCell != nullptr && neighborCell->pollution < currentPollution - 1) {
                        // Add the neighbor cell to the queue
                        cellQueue.push(make_pair(newX, newY));
                        pollutionQueue.push(currentPollution - 1);
                    }
                }
            }
        }
    }
}
