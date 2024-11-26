#include "Commercial.h"
#include "Region.h"
#include <iostream>

//ctor for commercial cell that initializes it with zone type 'C' and associates it with a region
Commercial::Commercial(int x, int y, Region* region) : Cell('C', x, y, region) {}

//a cloning function for the bonus
Commercial* Commercial::clone() const {
        return new Commercial(*this);
}

//handles the growth logic for a commercial cell
void Commercial::grow(){
    //x&y-coordinates of the cell
    int x = this->x;
    int y = this->y;

    //check conditions required for growth
    bool nearPowerline = region->adjToPowerline(x, y); 
    int availableWorkers = region->getAvailableWorkers(); 
    int availableGoods = region->getAvailableGoods();
    int nearbyPopulatedCells = region->getCountPopulatedAdjCell(x, y, 0); 

    if (this->population == 0) //if population = 0, check initial growth conditions
    {   
        if ((nearPowerline || nearbyPopulatedCells >= 1) && availableWorkers >= 1 && availableGoods >= 1)
        {
            //if initial growth conditions are met increase poplation and consume one worker and one good
            this->population += 1;
            region->modifyAvailableGoods(-1);
            region->modifyAvailableWorkers(-1);
        }
        
    }else if (this->population == 1)//if population = 1, check other growth conditions
    {
        if (nearbyPopulatedCells >= 2 && availableWorkers >= 1 && availableGoods >= 1)
        {
            this->population += 1;
            region->modifyAvailableGoods(-1);
            region->modifyAvailableWorkers(-1);
        }
        
    }

}