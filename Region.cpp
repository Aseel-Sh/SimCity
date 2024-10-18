#include "Region.h"
#include "Commercial.h"
#include <fstream>
#include <sstream>
#include <iostream>


// Constructor for the cell the initilizes the zoneType
Cell::Cell(char zoneType) : zoneType(zoneType) {}

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
                grid[row][col] = new Commercial(); //create a commerical cell if zonetype is C
                break;
            default:
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
            std::cout << cell->zoneType << " "; //changed "." to "->" since its a ptr now
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