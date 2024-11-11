#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Region.h"


class Residential: public Cell {

    public:
    // Constructor
    Residential(int x, int y, Region* region);
    void grow() override; // grow override funct.


};

#endif // RESIDENTIAL_H