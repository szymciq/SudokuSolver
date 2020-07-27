#ifndef VARIABLES_H
#define VARIABLES_H

#include <set>
#include <utility>
#include <vector>
#include <cstdlib>
#include <chrono>

using Point = std::pair<int, int>;
using PossibleValues = std::vector<int>;
using PointWithPossibleValues = std::pair<Point, PossibleValues>;

constexpr int EMPTY = 0;
constexpr int GRID_SIZE = 9;

int getRandom(int min, int max);
template <typename T>
void swap(T& a, T& b);


#endif