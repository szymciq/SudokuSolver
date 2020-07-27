#include "Sudoku.h"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <iomanip>

Sudoku::Sudoku()
: grid(Grid()), numberOfSteps(0) { };

Sudoku::Sudoku(const Grid& grid)
: grid(grid), numberOfSteps(0) { }

bool Sudoku::isSolvable() const {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++) {
            Point p(i, j);
            if (!grid.getCell(p).isEmpty()) {
                int value = grid.getCell(p).getValue();
                grid.getCell(p).setValue(EMPTY);
                bool result = grid.canInsertValueIntoCell(value, p);
                grid.getCell(p).setValue(value);
                if (!result)
                    return false;
            }
        }
    return true;
}

void Sudoku::solve() {
    if (isSolvable()) {
        std::cout << std::fixed << std::setprecision(4);
        auto startTime = std::chrono::steady_clock::now();
        bool solved = doSolveStep();
        auto finishTime = std::chrono::steady_clock::now();
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(finishTime - startTime).count();
        if (solved) {
            std::cout 
                << "I solved your puzzle in " << numberOfSteps << " steps\n"
                << "I spent " << time / 1000 << " s on it..\n"
                << "Solution: \n";
            printGrid();
        } else {
            std::cout 
                << "This puzzle is too hard for me :(\n"
                << "After " << numberOfSteps << " steps I think it's impossible to solve it!\n"
                << "I spent " << time / 1000 << " s on it..\n";
        }
    } else {
        std::cout 
            << "There is a little bug in your grid\n"
            << "I can't solve it :(\n";
    }
}

bool Sudoku::doSolveStep() {
    numberOfSteps++;
    if (grid.countEmptyCells() == 0)
        return true;
    else {
        auto [p, possibleValues] = grid.getCellWithFewestPossibilities();
        if (possibleValues.size() == 0)
            return false;
        else {
            std::random_shuffle(possibleValues.begin(), possibleValues.end()); // solution repeats less frequently
            for (auto value : possibleValues) {
                grid.getCell(p).setValue(value);
                if (doSolveStep()) {
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