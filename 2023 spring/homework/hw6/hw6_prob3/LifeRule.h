#ifndef LIFERULE_H__
#define LIFERULE_H__

#include <vector>
#include "LifeCell.h"

class GameWorld;

// Cell Neighbors

/**
 * Base Class of Rules
 *
 * Determines the next state of a cell based on the current state and the number of live neighbors
 *
 */
class LifeRuleBase
{
public:
    LifeRuleBase() = default;
    virtual ~LifeRuleBase() = default;

    /**
     * @brief Determines the next state of a cell `current`, based on the current state and the number of live neighbors
     *
     * 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
     * 2. Any live cell with two or three live neighbours lives on to the next generation.
     * 3. Any live cell with more than three live neighbours dies, as if by over-population.
     * 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
     *
     * @param current A pointor to a cell to be updated
     * @param neighbors a vector of `CellPointer`, containing all the neighbors of the cell we working on. You need to count the number of living cells in neighbors to determine the next state.
     */
    virtual void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors);

    /**
     * @brief Get neighbors from map
     *
     * @param game_world Current world,
     * @param x Row coordinate
     * @param y Col coordinate
     * @return CellNeighbors, vector of cells
     */
    virtual CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const;

    /**
     * @brief Count the number of alive neighbors
     *
     * @param neighbors
     * @return int
     */
    virtual int CountAliveNeighbors(const CellNeighbors &neighbors) const;

    /**
     * @brief Get the Rule Name object
     *
     * @return const std::string&
     */
    virtual const std::string GetRuleName() const { return "Base"; }
};

/**
 * @brief Colorised Rule
 *
 * You may want to inherit some functions from previous rules.
 * It **must** be a subclass of LifeRuleBase with implementation
 * of ``DetermineNextState`` and ``GetNeighbors``, some of them 
 * may need to be overriden.
 *
 */
class LifeRuleColorised : public LifeRuleBase
{
    void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;

    /**
     * @brief Get the Rule Name
     * 
     * For rule selection. DO NOT change this function.
     * 
     * @return const std::string, the name of the rule
     */
    virtual const std::string GetRuleName() const { return "Colorised"; } // DO NOT CHANGE THIS FUNCTION
};

/**
 * @brief Extended Rule
 *
 * You may want to inherit some functions from previous rules.
 * It **must** be a subclass of LifeRuleBase with implementation
 * of ``DetermineNextState`` and ``GetNeighbors``, some of them 
 * may need to be overriden.
 *
 */
class LifeRuleExtended : public LifeRuleBase
{
    CellNeighbors GetNeighbors(const GameWorld *const game_world, const int x, const int y) const override;
    /**
     * @brief Get the Rule Name
     * 
     * For rule selection. DO NOT change this function.
     * 
     * @return const std::string, the name of the rule
     */
    virtual const std::string GetRuleName() const { return "Extended"; } // DO NOT CHANGE THIS FUNCTION
};


/**
 * @brief Weighted Rule
 * 
 * You may want to inherit some functions from previous rules.
 * It **must** be a subclass of LifeRuleBase with implementation
 * of ``DetermineNextState`` and ``GetNeighbors``, some of them 
 * may need to be overriden.
 * 
 */
class LifeRuleWeighted : public LifeRuleExtended
{
    void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;
    int AddWeight(const CellPointer &current, const CellNeighbors &neighbors) const;
    /**
     * @brief Get the Rule Name
     * 
     * For rule selection. DO NOT change this function.
     * 
     * @return const std::string, the name of the rule
     */
    virtual const std::string GetRuleName() const { return "Weighted"; } // DO NOT CHANGE THIS FUNCTION
};

/**
 * @brief Generations Rule
 * 
 * You may want to inherit some functions from previous rules.
 * It **must** be a subclass of LifeRuleBase with implementation
 * of ``DetermineNextState`` and ``GetNeighbors``, some of them 
 * may need to be overriden.
 *
 */
class LifeRuleGenerations : public LifeRuleBase
{
    void DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) override;
    /**
     * @brief Get the Rule Name
     * 
     * For rule selection. DO NOT change this function.
     * 
     * @return const std::string, the name of the rule
     */
    virtual const std::string GetRuleName() const { return "Generations"; } // DO NOT CHANGE THIS FUNCTION
};

using LifeRulePointer = std::shared_ptr<LifeRuleBase>;

#endif // LIFERULE_H__