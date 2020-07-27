#include <fstream>
#include <iostream>
#include <cmath>
#include <utility>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Grid.h"

Grid::Grid() {
    this->grid = new Cell*[GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        this->grid[i] = new Cell[GRID_SIZE];
    }
}

Grid::Grid(const Grid& g)
: Grid() {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            getCell(Point(i,j)).setValue(g.getCell(Point(i,j)).getValue());
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
                    if (c == '\n' || c == ' ') {
                        j--;
                        continue;
                    }
                    int value = c - '0';
                    if (value != EMPTY && (value < 1 || value > 9)) {
                        std::cout << value;
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

Cell& Grid::getCell(const Point& p) const {
    return grid[p.first][p.second];
};

int Grid::countEmptyCells() const {
    int count = 0;
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            if (getCell(Point(i, j)).isEmpty())
                count++;
    return count;
}

bool Grid::isValueInRow(int value, int row) const {
    for (int i = 0; i < GRID_SIZE; i++)
        if (getCell(Point(row, i)).getValue() == value)
            return true;
    return false;
}

bool Grid::isValueInCol(int value, int col) const {
    for (int i = 0; i < GRID_SIZE; i++)
        if (getCell(Point(i, col)).getValue() == value)
            return true;
    return false;
}

bool Grid::isValueInSquare(int value, Point p) const {
    int sq = sqrt(GRID_SIZE);
    int startRow = p.first / sq * sq;
    int startCol = p.second / sq * sq;
    for (int i = 0; i < sq; i++)
        for (int j = 0; j < sq; j++)
            if (getCell(Point(i + startRow, j + startCol)).getValue() == value)
                return true;
    return false;
}

bool Grid::canInsertValueIntoCell(int value, const Point& p) const {
    return !(isValueInRow(value, p.first) || isValueInCol(value, p.second) || isValueInSquare(value, p));
}

void Grid::printGrid() const {
    int sq = sqrt(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            std::cout << getCell(Point(i, j)).getValue() << " ";
            if ((j + 1) % sq == 0)
                std::cout << " ";
        }
        std::cout << std::endl;
        if ((i + 1) % sq == 0)
                std::cout << std::endl;
    }
}

PossibleValues Grid::getPossibleValues(const Point& p) const {
    PossibleValues possibleValues;
    for (int i = 1; i <= GRID_SIZE; i++)
        if (canInsertValueIntoCell(i, p))
            possibleValues.push_back(i);
    return possibleValues;
}

PointWithPossibleValues Grid::getCellWithFewestPossibilities() const {
    PossibleValues possibleValues { 1,2,3,4,5,6,7,8,9,10 };
    Point p(-1, -1);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            Point currP(i, j);
            if (!getCell(currP).isEmpty())
                continue;
            auto currPossibleValues = getPossibleValues(currP);
            if (currPossibleValues.size() < possibleValues.size()) {
                possibleValues = currPossibleValues;
                p = currP;
                if (possibleValues.size() == 0) {
                    i = j = 9;
                }
            }
        }
    return PointWithPossibleValues(p, possibleValues);
}

Grid Grid::operator=(const Grid& g) {
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            getCell(Point(i, j)).setValue(g.getCell(Point(i, j)).getValue());
    return *this;
}

Grid Grid::generateRandomGrid(int numberOfFilledCells) {
    if (numberOfFilledCells < 0)
        numberOfFilledCells = 0;
    if (numberOfFilledCells > (GRID_SIZE * GRID_SIZE) / 2)
        numberOfFilledCells = GRID_SIZE * GRID_SIZE / 2;

    Grid randomGrid;
    
    int numberOfEmptyCells = (GRID_SIZE * GRID_SIZE) - numberOfFilledCells;
    while (!randomGrid.fillCells(numberOfEmptyCells))
        continue;

    return randomGrid;
}

bool Grid::fillCells(int numberOfEmptyCells) {
    if (countEmptyCells() <= numberOfEmptyCells)
        return true;
    Point p(getRandom(0, GRID_SIZE - 1), getRandom(0, GRID_SIZE - 1));
    while (!getCell(p).isEmpty())
        p = Point(getRandom(0, GRID_SIZE - 1), getRandom(0, GRID_SIZE - 1));
    PossibleValues possibleValues = getPossibleValues(p);
    std::random_shuffle(possibleValues.begin(), possibleValues.end());
    for (auto value : possibleValues) {
        getCell(p).setValue(value);
        if (fillCells(numberOfEmptyCells))
            return true;
    }
    getCell(p).setValue(EMPTY);
    return false;
}