#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "Region.h"

class Commercial : public Cell {
    public: 
    Commercial() : Cell('C') {}
    void grow() override; // this is the func that will override our base class's grow
};

#endif