#include <iostream>

class LivingThing {
public:
    void breathe() {
        std::cout << "I'm breathing as a living thing." << std::endl;
    }
};

class Animal : public LivingThing {

};

class Reptile : public LivingThing {

};

class Snake : public Animal, public Reptile {

};

int main() {
    Snake snake;
    snake.breathe();

    return 0;
}