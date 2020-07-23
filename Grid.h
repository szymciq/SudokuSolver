#ifndef GRID_H
#define GRID_H

#include <utility>
#include <string>
#include "Cell.h"

using Point = std::pair<int, int>;

class Grid {
    private:
        Cell** grid;
    public:
        Grid();
        Grid(const std::string& filename);
        ~Grid();
        static Grid generateRandomGrid(int numberOfEmptyCells);
        Cell& getCell(Point p) const;
        int countEmptyCells() const;
};

#endif
