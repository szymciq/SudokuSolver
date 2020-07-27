cmake_minimum_required(VERSION 3.10)
project(SudokuSolver)
set(CMAKE_CXX_STANDARD 17)
add_executable(SudokuSolver Functions.cpp Cell.cpp Grid.cpp Sudoku.cpp main.cpp)