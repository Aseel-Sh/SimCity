#include "Commercial.h"
#include "Region.h"
#include <iostream>

Commercial::Commercial(int x, int y, Region* region) : Cell('C', x, y, region) {}

void Commercial::grow(){
    int x = this->x;
    int y = this->y;

    if (this->population == 0)
    {
        bool nearPowerline = region->adjToPowerline(x, y);
    }
    

}