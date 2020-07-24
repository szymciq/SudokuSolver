#ifndef VARIABLES_H
#define VARIABLES_H

#include <set>
#include <utility>

using Point = std::pair<int, int>;
using PossibleValues = std::set<int>;
using PointWithPossibleValues = std::pair<Point, PossibleValues>;

constexpr int EMPTY = 0;
constexpr int GRID_SIZE = 9;

#endif