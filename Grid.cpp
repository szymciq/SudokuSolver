#ifndef GRID_H
#define GRID_H

#include <utility>
#include "Cell.h"

using Point = std::pair<int, int>;
inline constexpr int GRID_SIZE = 9;

class Grid {
    private:
        Cell grid[GRID_SIZE][GRID_SIZE];
    public:
        Grid();
        const Cell& getCell(Point p) const;
        void x() {
            auto x = getCell(Point(1,1));
            x.setValue(10);
        }
};

#endif
