#ifndef OTHERREGION_H
#define OTHERREGION_H

#include "Region.h"

class OtherRegion : public Cell {
    public:
    OtherRegion(char zoneType) : Cell(zoneType) {}
    void grow() override {}
};

#endif