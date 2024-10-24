#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "Region.h" 
#include <vector> 
using namespace std;

// Function declarations
bool growIndustrialZone(Cell& cell, const vector<vector<Cell>>& region, int x, int y, int& availableWorkers);


#endif // INDUSTRIAL_H
