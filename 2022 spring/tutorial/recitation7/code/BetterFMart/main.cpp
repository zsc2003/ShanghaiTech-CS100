#include <iostream>
#include "Game.hpp"

using std::cin;

int main() {
    int rows, cols;
    cin >> rows >> cols;
    Game game(rows, cols);
    game.play();
    return 0;
}