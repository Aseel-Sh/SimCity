#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "Region.h" 
#include <vector>


class Industrial : public Cell {
public:
    Industrial(int x, int y, Region* region);
    
   
    void grow() override;
    virtual Industrial* clone() const override;
    
   
    void spreadPollution();
};

#endif // INDUSTRIAL_H
