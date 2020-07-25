#include <iostream>
#include "Sudoku.h"

int main() {
    Grid exampleGridFromFile("exampleGrid.txt");
    Grid emptyGrid();
    Grid randomGrid = Grid::generateRandomGrid(60);
    

    Grid& grid = exampleGridFromFile;


    Sudoku s(grid);
    std::cout << "Your grid: \n";
    s.printGrid();
    s.solve();
    
    return 0;
}