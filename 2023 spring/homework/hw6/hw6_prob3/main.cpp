#include <memory>
#include <iostream>
#include "GameManager.h"

const int gridWidth = 25;
const int gridHeight = 25;

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        std::cout << "Please provide the rule type in a command line argument!" << std::endl;
        return 1;
    }
    std::string rule_type = argv[1];

    GameWorld world = GameWorld(gridWidth, gridHeight, rule_type);
    GameManager gameManager(std::make_shared<GameWorld>(world));

    gameManager.StartGame();
    
    return 0;
}