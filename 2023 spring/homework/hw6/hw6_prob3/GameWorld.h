#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <vector>
#include <iostream>
#include <memory>
#include "LifeCell.h"
#include "LifeRule.h"

/**
 * World of the Game
 *
 * The GameWorld class is responsible for managing the game world.
 * It contains the current state of the world and the next state of the world
 * and the rule that determines the next state of each cell.
 *
 */
class GameWorld
{

public:
    GameWorld() = delete;
    GameWorld(
        const int width,
        const int height,
        const std::shared_ptr<LifeRuleBase> &rule);
    // Select rule based on string
    GameWorld(const int width, const int height, std::string rule_type);
    ~GameWorld() = default;

    /**
     * @brief Updates the world to next tick
     *
     */
    void Update();

    /**
     * @brief Update a cell to next state, determined by its neighbors
     *
     * @param cell a cell to update
     * @param neighbors its neighbors
     */
    void CellUpdate(const CellPointer &cell, const CellNeighbors &neighbors) const { m_rule->DetermineNextState(cell, neighbors); }

    // Getters
    int GetWidth() const { return m_width; }

    int GetHeight() const { return m_height; }

    CellPointer GetCell(const int x, const int y) const { return m_map[x][y]; }

    // Get Rule Name
    const std::string GetRuleName() const { return m_rule->GetRuleName(); }

    /**
     * @brief Get string of the world
     *
     * Used for OJ to check your answer
     *
     * @return std::string
     */
    std::string GetWorldStr() const;

    /**
     * @brief Get the world map
     * 
     * @return const WorldMap2d& 
     */
    const WorldMap2d &GetWorldMap() const { return m_map; }

    /**
     * @brief Get the neighbors using corresponding rule
     * 
     * @param x, y the position of the cell
     * @return CellNeighbors, the neighbors of the cell
     */
    CellNeighbors GetNeighbors(const int x, const int y) const { return m_rule->GetNeighbors(this, x, y); }

    /**
     * @brief Check if the position is valid
     * 
     * @param x, y a position
     * @return true if the position is valid, false if the position is invalid
     */
    bool CheckPosValid(const int x, const int y) const { return (x >= 0 && x < GetHeight()) && (y >= 0 && y < GetWidth()); }

    // Setters
    /**
     * @brief Set the cell state 
     * 
     * @param x, y the position of the cell
     * @param state 
     */
    void SetCell(const int x, const int y, const int state)
    {
        m_map[x][y]->SetState(state);
    }

private:
    WorldMap2d m_map;
    WorldMap2d m_mapNext;
    std::shared_ptr<LifeRuleBase> m_rule;
    const int m_width;
    const int m_height;
};

#endif