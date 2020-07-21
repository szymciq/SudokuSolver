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