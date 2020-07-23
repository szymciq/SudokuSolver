#include <fstream>
#include <iostream>
#include "Grid.h"

Grid::Grid() {
    this->grid = new Cell*[9];
    for (int i = 0; i < GRID_SIZE; i++) {
        this->grid[i] = new Cell[GRID_SIZE];
    }
}

Grid::Grid(const std::string& filename)
: Grid() {
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
                            this->grid[m][n] = EMPTY;
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
                                this->grid[m][n].setValue(EMPTY);
                            }
                        }
                        i = j = 9;
                    } else {
                        this->grid[i][j].setValue(value);
                    }
                }
            }
    }
    file.close();
}

Grid::~Grid() {
    for (int i = 0; i < GRID_SIZE; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

Cell& Grid::getCell(Point p) const {

};

int Grid::countEmptyCells() const {

}

bool Grid::isValueInRow(int value, int row) {

}

bool Grid::isValueInCol(int value, int col) {

}

bool Grid::isValueInSquare(int value, Point p) {

}

Grid Grid::generateRandomGrid(int numberOfEmptyCells) {

}