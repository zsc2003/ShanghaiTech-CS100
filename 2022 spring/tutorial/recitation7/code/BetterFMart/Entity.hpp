//
// Created by llk89 on 2019/10/24.
// Copyright (c) 2019 llk89 All rights reserved.
//

#ifndef RECITATION5_ENTITY_HPP
#define RECITATION5_ENTITY_HPP


#include "Game.hpp"
#include "MealType.hpp"

// Solve circular dependency
class Game;

class Entity {
public:
    Entity(Game *game, int row, int col);
    /// Respond to user input
    /// \param action user input
    /// \return whether the game ends
    virtual bool onAction(char action);
    /// Do something before getting user input
    /// Preferably used to render some important info
    /// Like how many lives this player has
    virtual void preRender() const;
    /// Render myself inside the grid
    /// \param grid the grid
    virtual void render(char **grid) const;
    /// Respond to a player sending meals
    /// \param meal the meal being sent
    /// \return whether the meal is accepted
    virtual bool receive(MealType meal);
    int getColumn() const;
    int getRow() const;
    // TODO maybe you need to add some more methods?
protected:
    Game *m_game;
    int m_row, m_col;
};


#endif //RECITATION5_ENTITY_HPP
