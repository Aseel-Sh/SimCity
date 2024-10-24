#include "Industrial.h"
#include <iostream>
#include <vector>

using namespace std;


bool isAdjacentToPowerline(const vector<vector<Cell>>& region, int x, int y) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < 8; i++) {
        int newX = x + directions[i][0];
        int newY = y + directions[i][1];
        if (newX >= 0 && newX < region.size() && newY >= 0 && newY < region[0].size()) {
            if (region[newX][newY].zoneType == 'T') { 
                return true;
            }
        }
    }
    return false;
}


bool growIndustrialZone(Cell& cell, const vector<vector<Cell>>& region, int x, int y, int& availableWorkers) {
    if (cell.zoneType != 'I') return false; 
    if (availableWorkers < 2) return false; 

    
    if (isAdjacentToPowerline(region, x, y) || cell.population > 0) {
        
        if (cell.population == 0 && availableWorkers >= 2) {
            cell.population++;
            availableWorkers -= 2;
            return true;
        }
    }
    return false;
}

