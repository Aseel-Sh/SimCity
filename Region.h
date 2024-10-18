#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

class Cell {
    public:
        // This represents the zone type of a cell, Residential, industrial and so on and its type char cause each zone is represented by such
        char zoneType;
        int population;
        int goods;
        int workers;
        // This is the constructor that initilizes the zoneType when the Cell object is created
        Cell(char zoneType = '-'); // defaults the place holder to roads
        virtual void grow()= 0; //the abstract grow func, will differ based on cell zone type

};

class Region {
    private:
        int rows, cols;
        // Created a grid of Cell type, Each cell represents an object or a unit such as a residential, industrial zone
        std::vector<std::vector<Cell*>> grid; //made it a pointer as opposed to the object itself - Aseel

    public:
        // Gives the simiualtion the correct dimensions
        Region(int rows, int cols);
        void loadRegion(const std::string& fileName);
        void printRegion() const;

        // Finds the region size
        static void getRegionSize(const std::string& fileName, int& rows, int& cols);
};

#endif