//
// Created by llk89 on 2019/10/24.
// Copyright (c) 2019 llk89 All rights reserved.
//

#include "Entity.hpp"

Entity::Entity(Game *game, int row, int col)
        : m_game(game), m_row(row), m_col(col) {}

bool Entity::onAction(char action) {
    //TODO YOUR CODE HERE
    // You should add a default behavior here
    // If you think it is impossible, make it pure virtual instead
    return false;
}

void Entity::preRender() const {
    //TODO YOUR CODE HERE
    // You should add a default behavior here
    // If you think it is impossible, make it pure virtual instead
}

void Entity::render(char **grid) const {
    //TODO YOUR CODE HERE
    // You should add a default behavior here
    // If you think it is impossible, make it pure virtual instead
}

bool Entity::receive(MealType meal) {
    //TODO YOUR CODE HERE
    // You should add a default behavior here
    // If you think it is impossible, make it pure virtual instead
    return false;
}

int Entity::getColumn() const {
    return m_col;
}

int Entity::getRow() const {
    return m_row;
}
