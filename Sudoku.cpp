#include "Sudoku.h"
#include <chrono>
#include <iostream>
#include <fstream>

Sudoku::Sudoku()
: numberOfSteps(0), solvingTime(0.0f) {
    this->initialGrid = new int*[9];
    this->currentGrid = new int*[9];
    for (int i = 0; i < 9; i++) {
        this->initialGrid[i] = new int[9];
        this->currentGrid[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            this->initialGrid[i][j] = this->currentGrid[i][j] = EMPTY;
        }
    }
}

Sudoku::Sudoku(const std::string& filename)
: Sudoku() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Can't open file, using empty grid\n";
    } else {
        char c;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (file.eof()) {
                    std::cout << "File is not valid, using empty grid\n";
                    for (int m = 0; m < i; m++) {
                        for (int n = 0; n < j; n++) {
                            this->initialGrid[m][n] = this->currentGrid[m][n] = EMPTY;
                        }
                    }
                    i = j = 9;
                } else {
                    file >> c;
                    int value = '0' - c;
                    if (value != EMPTY && (value < 1 || value > 9)) {
                        std::cout << "Grid in this file is not valid, using empty grid\n";
                        for (int m = 0; m < i; m++) {
                            for (int n = 0; n < j; n++) {
                                this->initialGrid[m][n] = this->currentGrid[m][n] = EMPTY;
                            }
                        }
                        i = j = 9;
                    }
                }
            }
    }
    file.close();
}

Sudoku::Sudoku(const int** grid)
: Sudoku() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (grid[i][j] != EMPTY && (grid[i][j] < 1 || grid[i][j] > 9)) {
                std::cout << "Incorrect value in input grid, using empty grid\n";
                for (int m = 0; m < i; m++) {
                        for (int n = 0; n < j; n++) {
                            this->initialGrid[m][n] = this->currentGrid[m][n] = EMPTY;
                        }
                    }
                i = j = 9;
            } else {
                initialGrid[i][j] = currentGrid[i][j] = grid[i][j];
            }
}

Sudoku::Sudoku(const int grid[9][9])
: Sudoku() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (grid[i][j] != EMPTY && (grid[i][j] < 1 || grid[i][j] > 9)) {
                std::cout << "Incorrect value in input grid, using empty grid\n";
                for (int m = 0; m < i; m++) {
                        for (int n = 0; n < j; n++) {
                            this->initialGrid[m][n] = this->currentGrid[m][n] = EMPTY;
                        }
                    }
                i = j = 9;
            } else {
                initialGrid[i][j] = currentGrid[i][j] = grid[i][j];
            }
}

Sudoku::~Sudoku() {
    for (int i = 0; i < 9; i++) {
        delete initialGrid[i];
        delete currentGrid[i];
    }
    delete initialGrid;
    delete currentGrid;
}

bool Sudoku::solve() {
    auto startTime = std::chrono::steady_clock::now();
    bool solved = doSolveStep();
    auto endTime = std::chrono::steady_clock::now();
    solvingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    return solved;   
}

void Sudoku::printCurrentGrid() const {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << currentGrid[i][j] << " ";
            if ((j + 1) % 3 == 0)
                std::cout << " ";
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
}

void Sudoku::printInitialGrid() const {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << initialGrid[i][j] << " ";
            if ((j + 1) % 3 == 0)
                std::cout << " ";
        }
        std::cout << std::endl;
        if ((i + 1) % 3 == 0)
            std::cout << std::endl;
    }
}

int Sudoku::countEmptyCells() const {
    int count = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (currentGrid[i][j] == EMPTY)
                count++;
    return count;
}

int Sudoku::getNumberOfSteps() const {
    return numberOfSteps;
}

float Sudoku::getSolvingTime() const {
    return solvingTime;
}

bool Sudoku::doSolveStep() {
    numberOfSteps++;
    auto [emptyCell, possibleValues] = getCellWithFewestPossibilities();
    if (emptyCell.first == -1 && emptyCell.second == -1)
        return true; // puzzle is solved :)
    else if (possibleValues.size() == 0)
        return false; // grid can't be solved
    else {
        for (auto value : possibleValues) {
            setValueInCell(value, emptyCell);
            if (doSolveStep())
                return true;
        }
    }
    return false;
}

bool Sudoku::isValueInRow(int value, int row) const {
    for (int i = 0; i < 0; i++) {
        auto val = getValue(Cell(row, i));
        if (value == val && val != EMPTY)
            return true;        
    }
    return false;
}

bool Sudoku::isValueInCol(int value, int col) const {
    for (int i = 0; i < 0; i++) {
        auto val = getValue(Cell(i, col));
        if (value == val && val != EMPTY)
            return true;        
    }
    return false;
}

bool Sudoku::isValueInSquare(int value, const Cell& cell) const {
    int startRow = cell.first / 3 * 3;
    int startCol = cell.second / 3 * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            auto val = getValue(Cell(i + startRow, j + startCol));
            if (value == val && val != EMPTY)
                return true;
        }
    return false;
}

bool Sudoku::canInsertValueIntoCell(int value, const Cell& cell) const {
    return !(isValueInRow(value, cell.first) || isValueInCol(value, cell.second) || isValueInSquare(value, cell));
}

int Sudoku::getValue(const Cell& cell) const {
    return currentGrid[cell.first][cell.second];
}

void Sudoku::setValueInCell(int value, const Cell& cell) {
    if (value == EMPTY || (value >= 1 && value <= 9)) {
        currentGrid[cell.first][cell.second] = value;
    }
}

PossibleValues Sudoku::getPossibleValues(const Cell& cell) const {
    PossibleValues possibleValues;
    for (int i = 1; i <= 9; i++)
        if (canInsertValueIntoCell(i, cell))
            possibleValues.insert(i);
    return possibleValues;
}

CellWithPossibleValues Sudoku::getCellWithFewestPossibilities() const {
    PossibleValues possibleValues { 1,2,3,4,5,6,7,8,9 };
    Cell cell(-1, -1);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            auto currPossibleValues = getPossibleValues(Cell(i, j));
            if (currPossibleValues.size() < possibleValues.size()) {
                possibleValues = currPossibleValues;
                cell = Cell(i, j);
                if (possibleValues.size() == 0) {
                    i = j = 9;
                }
            }
        }
    return CellWithPossibleValues(cell, possibleValues);
}