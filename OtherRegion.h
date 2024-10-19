#ifndef OTHERREGION_H
#define OTHERREGION_H

#include "Region.h"

class OtherRegion : public Cell {
    public:
    OtherRegion(char zoneType, int x, int y) : Cell(zoneType, x, y) {}
    void grow() override {}
};

#endif