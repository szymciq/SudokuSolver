#ifndef GRID_H
#define GRID_H

#include <string>
#include "Variables.h"
#include "Cell.h"

class Grid {
    private:
        Cell** grid;
    public:
        Grid();
        Grid(const std::string& filename);
        ~Grid();
        Cell& getCell(Point p) const;
        int countEmptyCells() const;
        bool isValueInRow(int value, int row);
        bool isValueInCol(int value, int col);
        bool isValueInSquare(int value, Point p);

        static Grid generateRandomGrid(int numberOfEmptyCells);
};

#endif
