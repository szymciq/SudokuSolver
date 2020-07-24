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
        static Grid generateRandomGrid(int numberOfEmptyCells = GRID_SIZE * GRID_SIZE);
};

#endif
