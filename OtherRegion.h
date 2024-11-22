#ifndef OTHERREGION_H
#define OTHERREGION_H

#include "Region.h"

class OtherRegion : public Cell {
    public:
    OtherRegion(char zoneType, int x, int y, Region* region) : Cell(zoneType, x, y, region) {}
    void grow() override {}
    virtual OtherRegion* clone() const override {
        return new OtherRegion(*this);
    }
};

#endif