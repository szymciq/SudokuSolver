#ifndef SUDOKU_H
#define SUDOKU_H
#include <utility>
#include <string>
#include <set>

constexpr int EMPTY = 0;
using Cell = std::pair<int, int>;
using PossibleValues = std::set<int>;
using CellWithPossibleValues = std::pair<Cell, std::set<int>>;

class Sudoku {
    private:
        int** currentGrid;
        int** initialGrid;
        bool canBeSolved;
        bool isSolved;
        int numberOfSteps;
    public:
        Sudoku();
        Sudoku(const std::string& filename);
        Sudoku(const int** grid);
        Sudoku(const int grid[9][9]);
        ~Sudoku();
        bool solve();
        bool printCurrentGrid() const;
        bool printInitialGrid() const;
        int getValue(const Cell& cell) const;
        void setValueInCell(int value, const Cell& cell);
        int countEmptyCells() const;
        int getNumberOfSteps() const;
        bool isSolved() const;
    private:
        bool isValueInRow(int value, int row) const;
        bool isValueInCol(int value, int col) const;
        bool isValueInSquare(int value, const Cell& cell) const;
        bool canInsertValueIntoCell(int value, const Cell& cell) const;
        PossibleValues getPossibleValues(const Cell& cell) const;
        CellWithPossibleValues getCellWithFewestPossibilities() const;
};

#endif