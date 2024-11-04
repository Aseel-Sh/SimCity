#include "Commercial.h"
#include "Region.h"
#include <iostream>

Commercial::Commercial(int x, int y, Region* region) : Cell('C', x, y, region) {}

void Commercial::grow(){
    int x = this->x;
    int y = this->y;

    bool nearPowerline = region->adjToPowerline(x, y);
    int availableWorkers = region->getAvailableWorkers();
    int availableGoods = region->getAvailableGoods();
    int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 0);

    if (this->population == 0)
    {
        if ((nearPowerline || nearbyPopulatedCells >= 1) && availableWorkers >= 1 && availableGoods >= 1)
        {
            this->population += 1;
            region->modifyAvailableGoods(-1);
            region->modifyAvailableWorkers(-1);
        }
        
    }else if (this->population == 1)
    {
        if (nearbyPopulatedCells >= 2 && availableWorkers >= 1 && availableGoods >= 1)
        {
            this->population += 1;
            region->modifyAvailableGoods(-1);
            region->modifyAvailableWorkers(-1);
        }
        
    }

}