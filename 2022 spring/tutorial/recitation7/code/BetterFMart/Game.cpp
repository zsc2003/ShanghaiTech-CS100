//
// Created by temp on 2019/10/24.
//

#include "Game.hpp"
#include "Entity.hpp"
#include "Player.hpp"

// We use vector here. Forget it.

Game::Game(int rows, int cols) :
        m_entities(), rows(rows), cols(cols) {
    setEntity(rows / 2, 0, new Player(this, rows / 2, 0));
}

void Game::removeEntity(int row, int col) {
    for (auto iter = m_entities.begin(); iter != m_entities.end(); iter ++) {
        Entity *entity = *iter;
        if (entity->getRow() == row && entity->getColumn() == col) {
            m_entities.erase(iter);
            delete entity;
        }
    }
}

Entity *Game::getEntity(int row, int col) {
    for (const auto entity : m_entities) {
        if (entity->getRow() == row && entity->getColumn() == col)
            return entity;
    }
    return nullptr;
}

void Game::setEntity(int row, int col, Entity *entity) {
    removeEntity(row, col);
    m_entities.push_back(entity);
}

void Game::play() {
    // Stub
    // You may or may not implement this
}
