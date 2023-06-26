#include <cctype>
#include "LifeRule.h"
#include "GameWorld.h"
#include "GameSettings.h"

int LifeRuleBase::CountAliveNeighbors(const CellNeighbors &neighbors) const
{
    int count_alive = 0;            // Count the number of alive neighbors
    for (auto neighbor : neighbors) // Loop through all neighbors
    {
        if (neighbor->IsAlive()) // If the neighbor is alive
        {
            ++count_alive; // Then increase the count
        }
    }
    return count_alive; // Return the count

}

void LifeRuleBase::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors); // Count the number of alive neighbors

    // If the current cell is alive and the number of alive neighbors is not in the set of numbers that the cell survives with
    if (current->IsAlive() && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
    {
        current->SetState(CELL_STATE_DEAD);
        return;
    }
    // If the current cell is dead and the number of alive neighbors is in the set of numbers that the cell is born with
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        current->SetState(CELL_STATE_ALIVE);
        return;
    }

}

CellNeighbors LifeRuleBase::GetNeighbors(const GameWorld *const game_world, const int x, const int y) const
{
    // Get the neighbors of the cell at position x, y
    CellNeighbors neighbors;
    // Loop through all the neighbors
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
                continue;
            int next_x = x + i;
            int next_y = y + j;
            // If the position is not exceeding the boundaries of the world
            if (game_world->CheckPosValid(next_x, next_y))
            {
                // Add the neighbor to the list of neighbors
                neighbors.push_back(game_world->GetCell(next_x, next_y));
            }
        }
    }
    // Return the list of neighbors
    return neighbors;

}

void LifeRuleColorised::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors) 
{
    const int count_alive = CountAliveNeighbors(neighbors);
    int flag_red = 0;
    int flag_blue = 0;
    if (current->IsAlive() && (!BASE_CELL_SURVIVE_CONDITION.count(count_alive)))
    {
        current->SetState(CELL_STATE_DEAD);
        return;
    }
    if (!current->IsAlive() && BASE_CELL_BIRTH_CONDITION.count(count_alive))
    {
        for (auto neighbor : neighbors){
            if (neighbor->IsAlive()) {
                if(neighbor->GetState() == 2) ++flag_red;
                else ++flag_blue;
                }
            }
            
        
        if(flag_red >= 2) current->SetState(CELL_STATE_RED);
        else current->SetState(CELL_STATE_BLUE);
        
        return;
    }

}

CellNeighbors LifeRuleExtended::GetNeighbors(const GameWorld *const game_world, const int x, const int y) const 
{
    CellNeighbors neighbors;
    // Loop through all the neighbors
    for (int i = -2; i <= 2; ++i)
    {
        for (int j = -2; j <= 2; ++j)
        {
            if (i == 0 && j == 0)
                continue;
            int next_x = x + i;
            int next_y = y + j;
            // If the position is not exceeding the boundaries of the world
            if (game_world->CheckPosValid(next_x, next_y))
            {
                // Add the neighbor to the list of neighbors
                neighbors.push_back(game_world->GetCell(next_x, next_y));
            }
        }
    }
    // Return the list of neighbors
    return neighbors;

}

//WEIGHTED_CELL_SURVIVE_CONDITION = {4, 5, 6};
//WEIGHTED_CELL_BIRTH_CONDITION = {5, 6};
int LifeRuleWeighted::AddWeight(const CellPointer &current2, const CellNeighbors &neighbors) const
{
    int add_weight = 0;            // Count the number of alive neighbors
    for (auto neighbor : neighbors) // Loop through all neighbors
    {
        if (neighbor->IsAlive()) // If the neighbor is alive
        {
            if((abs(neighbor->GetX() - current2->GetX()) + abs(neighbor->GetY() - current2->GetY())) <= 2) add_weight +=2;
            else add_weight += 1; 
        }
    }
    return add_weight;
    
}

void LifeRuleWeighted::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    const int weight = AddWeight(current, neighbors);
    if (current->IsAlive() && (!WEIGHTED_CELL_SURVIVE_CONDITION.count(weight)))
    {
        current->SetState(CELL_STATE_DEAD);
        return;
    }
    // If the current cell is dead and the number of alive neighbors is in the set of numbers that the cell is born with
    if (!current->IsAlive() && WEIGHTED_CELL_BIRTH_CONDITION.count(weight))
    {
        current->SetState(CELL_STATE_ALIVE);
        return;
    }

}

void LifeRuleGenerations::DetermineNextState(const CellPointer &current, const CellNeighbors &neighbors)
{
    const int count_alive = CountAliveNeighbors(neighbors);
    if(current->GetState() == 0){
        if(BASE_CELL_BIRTH_CONDITION.count(count_alive)){
            current->SetState(1);
            return;
        }
        return;
    }
    else if(current->GetState() == 1) {
        if (BASE_CELL_SURVIVE_CONDITION.count(count_alive)) return;
        else{
            current->SetState(2);
            return;
        } 
    }
    else if (current->GetState() == 7){
        current->SetState(CELL_STATE_DEAD);
        return;
    } 
    else {
        current->SetState(current->GetState() + 1);
        return;
    }
}