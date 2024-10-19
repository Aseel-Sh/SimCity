#ifndef REGION_H
#define REGION_H

#include <vector>
#include <string>

class Region; // have to declare region before class so that i can add the ptr in cell

class Cell {
    public:
        // This represents the zone type of a cell, Residential, industrial and so on and its type char cause each zone is represented by such
        char zoneType;
        int x,y, population, goods, workers;
        Region* region; //ptr to region so that i can access region funcs in my commercial class
        // This is the constructor that initilizes the zoneType when the Cell object is created
        Cell(char zoneType = '-', int x = 0, int y = 0, Region* region = nullptr); // defaults the place holder to roads
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

        //a vector to store ptrs to the adj cells of curr cell
        std::vector<Cell*> getAdjacentCells(int x, int y) const;
        //shared funcs with all 3 zones
        bool adjToPowerline(int x, int y) const;
        //int getAvailableWorkers() const;
        //int getAvailableGoods() const;
        //int getAdjPopulation() const;


};

#endif