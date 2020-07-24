#ifndef SUDOKU_H
#define SUDOKU_H

#include "Grid.h"

class Sudoku {
    private:
        Grid grid;
    public:
        Sudoku();
        Sudoku(const Grid& grid);
        bool isSolvable() const;
        void solve();
        bool doSolveStep();
        void printGrid() const;
};

#endif