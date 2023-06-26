#ifndef GAMESETTING_H__
#define GAMESETTING_H__

#include <set>
#include <map>

#define CELL_STATE_DEAD 0
#define CELL_STATE_ALIVE 1
#define CELL_STATE_RED 2
#define CELL_STATE_BLUE 3

#define MAP_CELL_DEAD '.'
#define MAP_CELL_ALIVE 'O'
#define MAP_CELL_BLUE 'B'
#define MAP_CELL_RED 'R'

// For base rule states
const std::set<int> BASE_CELL_SURVIVE_CONDITION = {2, 3};
const std::set<int> BASE_CELL_BIRTH_CONDITION = {3};

// For weightened rule state
const std::set<int> WEIGHTED_CELL_SURVIVE_CONDITION = {4, 5, 6};
const std::set<int> WEIGHTED_CELL_BIRTH_CONDITION = {5, 6};

// For generations rule
#define MAX_GENERATIONS 8

// For map loading
const std::map<char, int> MAP_TO_STATE = {
    { MAP_CELL_DEAD, CELL_STATE_DEAD },
    { MAP_CELL_ALIVE, CELL_STATE_ALIVE },
    { MAP_CELL_BLUE, CELL_STATE_BLUE },
    { MAP_CELL_RED, CELL_STATE_RED }
};

#endif