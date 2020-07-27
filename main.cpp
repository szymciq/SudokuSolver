#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits>
#include "Sudoku.h"

int main() {
    const std::string filename = "exampleGrid.txt";

    std::srand(getRandom(0, std::numeric_limits<int>::max()));
    int option = 0;
    std::cout 
        << "Solve sudoku: \n"
        << "1. Empty grid\n"
        << "2. From file (\"" << filename << "\")\n"
        << "3. Random grid\n"
        << "Option: ";
    std::cin >> option;

    while (option < 1 || option > 3) {
        std::cout << "Incorrect option, try again: ";
        std::cin >> option;
        std::cin.clear();
        std::cin.ignore('\n');
    }

    Grid grid;
    if (option == 2) 
        grid = Grid(filename);
    else if (option == 3) 
        grid = Grid::generateRandomGrid(getRandom(0, (GRID_SIZE * GRID_SIZE / 2)));

    Sudoku sudoku(grid);
    std::cout << "Your grid: \n";
    sudoku.printGrid();
    sudoku.solve();
    
    return 0;
}