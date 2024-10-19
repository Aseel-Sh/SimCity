#include "Region.h"
#include "Commercial.h"
#include "OtherRegion.h"
#include <fstream>
#include <sstream>
#include <iostream>


// Constructor for the cell the initilizes the zoneType
Cell::Cell(char zoneType, int x, int y, Region* region) : zoneType(zoneType), x(x), y(y), region(region) {}

// Creates a 2d Vector grid with rows, where each row contains cols Cell objects
Region::Region(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<Cell*>(cols)) {} //also changed this to ptr - Aseel

// This reads the file and extracts the data from the csv file
void Region::loadRegion(const std::string& fileName) {
    std::ifstream regionFile(fileName);
    if (!regionFile.is_open()) {
        std::cerr << "Error opening region config file." << '\n';
        return;
    }

    std::string line;
    int row = 0;

    // Parses thru each line and creates the zoneType based of the letter or content it pulls in
    while (std::getline(regionFile, line) && row < rows) {
        std::stringstream ss(line);
        std::string cellValue;
        int col = 0;

        while (std::getline(ss, cellValue, ',') && col < cols) {
            //since we using inheritance I had to change this to create a cell based on type (eg an "I" will create a cell using "I" class) -Aseel
            //Yall can add ur stuff here I only added my part
            char zoneType = cellValue[0];
            switch (zoneType)
            {
            case 'C':
                grid[row][col] = new Commercial(row, col, this); //create a commerical cell if zonetype is C, passes x,y and this region
                break;
            case 'T':
            case '#':
            case 'P':
            case '-':
                grid[row][col] = new OtherRegion(zoneType, row, col);
                break;
            default:
                grid[row][col] = nullptr;
                break;
            }
            col++;
        }

        row++;
    }
}

// Prints the region based off of the values given from the csv file
void Region::printRegion() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if(cell != nullptr)
            {
                std::cout << cell->zoneType << " "; //changed "." to "->" since its a ptr now
            }else{
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
}

void Region::getRegionSize(const std::string& fileName, int& rows, int& cols) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
       std::cerr << "Error opening region file to find size" << '\n';
       return; 
    }

    std::string line;
    rows = 0;
    cols = 0;
    
    while (std::getline(file, line)) {
        rows++;
        std::stringstream ss(line);
        std::string cellValue;
        int currentCols = 0;

        //counts the columns
        while (std::getline(ss, cellValue, ',')) {
            currentCols++;
        }

        // sets cols 
        if (cols == 0) {
            cols = currentCols;
        }
    }
}

std::vector<Cell*> Region::getAdjacentCells(int x, int y) const {

    int n  = grid.size(); //num of rows

    std::vector<Cell*> adjCells;

    //deviation of row, checks rows up,curr,below. If there exists row above then set dx = -1 which will check that
    //else dx = 0, if dx not last row then set dx = 1 to check row below else set = 0
    for (int dx = (x > 0 ? -1 : 0); dx <= (x < n - 1 ? 1 : 0); dx++)
    {
        //deviation of col, col to left? dy = -1 else dy = 0. not last col? dy = 1 else dy = 0
        for (int dy = (y > 0 ? -1 : 0); dy <= (y < grid[x + dx].size() ? 1 : 0); dy++)
        {
            if (dx != 0 || dy != 0) //make sure we dont add the curr cell
            {
                //adj cell coordinates
                int newX = x + dx;
                int newY = y + dy;

                //since non uniform grid i have to check if the new coord is within bounds
                if (newX >= 0 && newX < n && newY >= 0 && newY < grid[newX].size())
                {
                    adjCells.push_back(grid[newX][newY]);
                }
                
            }
            
        }     
    }
    
    return adjCells;

}

bool Region::adjToPowerline(int x, int y) const {
    std::vector<Cell*> adjCells = getAdjacentCells(x, y);
    for (const auto& cell : adjCells)
    {
        if (cell->zoneType == 'T' || cell->zoneType =='#')
        {
            return true;
        }
    }
    return false;
    
}