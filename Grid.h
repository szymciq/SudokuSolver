#ifndef GRID_H
#define GRID_H

#include <string>
#include <set>
#include "Variables.h"
#include "Cell.h"


class Grid {
    private:
        Cell** grid;
    public:
        Grid();
        Grid(const Grid& g);
        Grid(const std::string& filename);
        ~Grid();
        Cell& getCell(const Point& p) const;
        int countEmptyCells() const;
        bool isValueInRow(int value, int row) const;
        bool isValueInCol(int value, int col) const;
        bool isValueInSquare(int value, Point p) const;
        bool canInsertValueIntoCell(int value, const Point& p) const;
        void printGrid() const;
        PossibleValues getPossibleValues(const Point& p) const;
        PointWithPossibleValues getCellWithFewestPossibilities() const;
        Grid operator=(const Grid& g);
        static Grid generateRandomGrid(int numberOfCellsToFill = 0); // fill up to 50% cells

        private:
        bool fillCells(int numberOfEmptyCells);        
};

#endif
