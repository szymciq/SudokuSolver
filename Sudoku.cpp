#include "Sudoku.h"

Sudoku::Sudoku()
: grid(Grid()) { };

Sudoku::Sudoku(const Grid& grid)
: grid(grid) { }

bool Sudoku::isSolvable() const {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++) {
            Point p(i, j);
            if (grid.getCell(p).isEmpty()) {
                if (grid.getPossibleValues(p).size() == 0)
                    return false;
            }
        }
    return true;
}

void Sudoku::solve() {
    doSolveStep();
}

bool Sudoku::doSolveStep() {
    if (grid.countEmptyCells() == 0)
        return true;
    else {
        auto [p, possibleValues] = grid.getCellWithFewestPossibilities();
        if (possibleValues.size() == 0)
            return false;
        else {
            for (auto value : possibleValues) {
                if (doSolveStep()) {
                    grid.getCell(p).setValue(value);
                    return true;
                }
            }
            grid.getCell(p).setValue(EMPTY);
        }
    }
    return false;
}

void Sudoku::printGrid() const {
    grid.printGrid();
}