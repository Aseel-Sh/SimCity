#include "Region.h"
#include "Commercial.h"
#include "Residential.h"
#include "Industrial.h"
#include "OtherRegion.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip> 


// Constructor for the cell the initilizes the zoneType
Cell::Cell(char zoneType, int x, int y, Region* region) : zoneType(zoneType), x(x), y(y), region(region) {}

// Creates a 2d Vector grid with rows, where each row contains cols Cell objects
Region::Region(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<Cell*>(cols)) {} //also changed this to ptr - Aseel

std::vector<std::vector<Cell*>> Region::cloneGrid() const {
    std::vector<std::vector<Cell*>> clonedGrid(rows, std::vector<Cell*>(cols, nullptr));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (grid[row][col] != nullptr) {
                clonedGrid[row][col] = grid[row][col]->clone();
            }
        }
    }

    return clonedGrid;
}

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
            case 'R':
                grid[row][col] = new Residential(row, col, this); //create a Residential cell if zonetype is R, passes x,y and this region
                break;
            case 'I':
                grid[row][col] = new Industrial(row, col, this); //create a Industrial cell if zonetype is I, passes x,y and this region
                break;
            case 'T':
            case '#':
            case 'P':
            case '-':
                grid[row][col] = new OtherRegion(zoneType, row, col, this);
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
            {   if (cell->population > 0)
                {
                    std::cout << cell->population << " "; //changed this to print population if there is any (like the ppt)
                }else{
                    std::cout << cell->zoneType << " "; //changed "." to "->" since its a ptr now
                }

            }else{
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
}

void Region::printRegionPollution() const {
    const int cellWidth = 6; 
    int totalpoll = 0;

    std::cout << "--------------------------------------\n";
    std::cout << "Pollution Final State: \n\n";

    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (cell != nullptr) {
                if (cell->population > 0) {
                    std::cout << std::setw(cellWidth - 3) << cell->population; 
                } else {
                    std::cout << std::setw(cellWidth - 3) << cell->zoneType; 
                }

                if (cell->pollution > 0) {
                    std::cout << "(" << cell->pollution << ")";
                    totalpoll+= cell->pollution;
                } else {
                    std::cout << "   "; 
                }
            } else {
                std::cout << std::setw(cellWidth) << " ";
            }
        }
        std::cout << std::endl << std::endl;
    }
    std::cout <<"Total Pollution: "<< totalpoll << std::endl;
    std::cout << "--------------------------------------\n\n";
}

void Region::getRegionSize(const std::string& fileName, int& rows, int& cols) {
    std::ifstream file("./" + fileName);
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

    std::vector<Cell*> adjCells;

    //deviation of row, checks rows up,curr,below. If there exists row above then set dx = -1 which will check that
    //else dx = 0, if dx not last row then set dx = 1 to check row below else set = 0
    for (int dx = (x > 0 ? -1 : 0); dx <= (x < rows - 1 ? 1 : 0); dx++)
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
                if (newX >= 0 && newX < rows && newY >= 0 && newY < grid[newX].size())
                {
                    if (grid[newX][newY] != nullptr) { //make sure not nullptr
                        adjCells.push_back(grid[newX][newY]);
                    }               
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

int Region::getCountPopulatedAdjCell(int x, int y, int population) const{
    std::vector<Cell*> adjCells = getAdjacentCells(x, y);
    int count = 0;
    for(const auto& cell : adjCells)
    {
        if (cell->population > 0 && cell->population >= population)
        {
            count++;
        }
        
    }
    
    return count;
}

int Region::getAvailableGoods() const{
    return goods;
}

int Region::getAvailableWorkers() const{
    return workers;
}

void Region::modifyAvailableGoods(int count){
    goods += count;
    if (goods < 0) //making sure it doesnt become negative
    {
        goods = 0;
    }
    
}

void Region::modifyAvailableWorkers(int count) {
    workers += count;
    if (workers < 0)
    {
        workers = 0;
    }
    
}

int Region::getTotalAdjacentPopulation(int x, int y) const {
    int totalPopulation = 0;
    std::vector<Cell*> adjacentCells = getAdjacentCells(x, y);
    for (const auto& cell : adjacentCells) {
        if (cell != nullptr) {
            totalPopulation += cell->population;
        }
    }
    return totalPopulation;
}


void Region::runSim(int timeLimit, int refreshRate){

    int timeStep = 0;
    int noChangesCount = 0;

    while (timeStep < timeLimit && noChangesCount < 2)
    {
        bool changed = false;

        for(auto& row : grid){
            for (auto& cell : row)
            {
                if (cell != nullptr)
                {
                    int initPopulation = cell->population;

                    cell->grow();

                    // Track changes in population (add pollution tracking later)
                    if (cell->population != initPopulation) 
                    {
                        changed = true;
                        break; //if changed then stop growth for this timestep
                    }
                    
                }
            }
            if (changed) break; //if changed then stop growth for this timestep
        }

        // Update the noChangesCount based on whether changes occurred
        if (!changed)
        {
            noChangesCount++;
        }else{
            noChangesCount = 0;
        }
        
        timeStep++;

        //only prints if there is change and our curr step is a multiple of our refresh rate
        if (changed && (timeStep % refreshRate == 0)) {
            std::cout << "Time step " << timeStep << ":" << std::endl;
            printRegion();
            std::cout << "Available Workers: " << getAvailableWorkers() << std::endl;
            std::cout << "Available Goods: " << getAvailableGoods() << std::endl<<std::endl;
        }
        
    }
    
}


void Region::printTotalPopulations() const{
    int totalRes = 0;
    int totalCom = 0;
    int totalInd = 0;

    for(auto& row : grid){
        for (auto& cell : row)
        {
           if (cell != nullptr)
           {    //since we might not have the char anymore Im using a dynamic cast to get type of object
                if (dynamic_cast<Residential*>(cell)){ //add residential print
                    totalRes += cell->population;
                }
                else if (dynamic_cast<Industrial*>(cell))
                {
                    totalInd += cell->population;
                }else if (dynamic_cast<Commercial*>(cell))
                {
                    totalCom += cell->population;
                }
                
           }
            
        }
    }

    std::cout << "Total Residential Population: " << totalRes<< std::endl;
    std::cout << "Total Industrial Population: " << totalInd<< std::endl;
    std::cout << "Total Commercial Population: " << totalCom<< std::endl;
    //will add rest later
    
}

void Region::selectArea(std::vector<std::vector<Cell*>> clonedGrid, int timeLimit, int refreshRate) const {
    int x1, y1;

    //ask user to select area
    std::cout << "Please select an area:\nTop-left coordinate x: ";
    std::cin >> x1;
    std::cout << "Top-left coordinate y: ";
    std::cin >> y1;

    //check if the are is within our grid
    while (x1 < 0 || y1 < 0 || x1 >= rows || y1 >= cols) {
        std::cout << "Out of bounds re-select an area:\nTop-left coordinate x: ";
        std::cin >> x1;
        std::cout << "Top-left coordinate y: ";
        std::cin >> y1;
    }

    int newRows = rows - x1;
    int newCols = cols - y1;

    Region* subRegion = new Region(newRows, newCols);

    for (int i = x1; i < rows; ++i) {
        for (int j = y1; j < cols; ++j) {
            if (clonedGrid[i][j] != nullptr) {
                subRegion->grid[i - x1][j - y1] = clonedGrid[i][j]->clone();
            }
        }
    }

    //delete old cloned grid to stop memory leaks
    for (auto& row : clonedGrid) {
        for (auto& cell : row) {
            delete cell;
        }
    }

    std::cout << "Initial sub-region state (Time step 0):" << std::endl;
    subRegion->printRegion();

    subRegion->runSim(timeLimit, refreshRate);

    subRegion->printTotalPopulations();
    subRegion->printRegionPollution();

    delete subRegion;

} 

int Region::getRows() const {
    return rows;
}

int Region::getCols() const {
    return cols;
} 

Cell* Region::getCell(int x, int y) const {
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        return grid[x][y];
    }
    return nullptr;
}