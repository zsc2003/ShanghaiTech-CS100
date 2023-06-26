#ifndef LIFECELL_H__
#define LIFECELL_H__
#include <string>
#include <vector>
#include <memory>
#include "GameSettings.h"

class LifeCell
{

public:
    LifeCell() : m_x(0), m_y(0), m_state(CELL_STATE_DEAD) {}
    LifeCell(const int x, const int y, const int state) : m_x(x), m_y(y), m_state(state) {}

    // Getters
    bool IsAlive() const { return m_state != CELL_STATE_DEAD; }
    int GetX() const { return m_x; }
    int GetY() const { return m_y; }
    int GetState() const { return m_state; }

    // Setters
    void SetState(const int state) { m_state = state; }
    void IncreaseState() { m_state++; }

private:
    int m_x, m_y;
    int m_state;
};

using CellPointer = std::shared_ptr<LifeCell>;
using CellNeighbors = std::vector<CellPointer>;
using WorldMapRow = std::vector<CellPointer>;
using WorldMap2d = std::vector<WorldMapRow>;

/**
 * @brief Create a Cell object based on the state
 *
 * The number of generation of the created cell is 1.
 *
 * @param x position of the cell
 * @param y position of the cell
 * @param type a char, indicate its type
 * @return CellPointer, created cell
 */
CellPointer CreateCell(const int x, const int y, const int state);

#endif