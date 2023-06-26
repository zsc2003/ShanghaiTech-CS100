//
// Created by llk89 on 2019/10/24.
//

#ifndef RECITATION5_GAME_HPP
#define RECITATION5_GAME_HPP

#include <vector>

// We use vector here. Forget it.
// You can search on internet to see what it is
// But for now, just treat it as a black box doing magic

class Entity;

class Game {
public:
    Game(int rows, int cols);
    void removeEntity(int row, int col);
    Entity *getEntity(int row, int col);
    void setEntity(int row, int col, Entity *entity);
    void play();

private:
    std::vector<Entity *> m_entities;
    int rows, cols;
};


#endif //RECITATION5_GAME_HPP
