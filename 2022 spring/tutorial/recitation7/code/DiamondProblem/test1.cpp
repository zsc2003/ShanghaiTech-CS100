#include <iostream>

class LivingThing {
public:
    void breathe() {
        std::cout << "I'm breathing as a living thing." << std::endl;
    }
};

class Animal : public LivingThing {
public:
    void breathe() {
        std::cout << "I'm breathing as an animal." << std::endl;
    }
};

class Reptile : public LivingThing {
public:
    void breathe() {
        std::cout << "I'm breathing as a reptile." << std::endl;
    }
};

class Snake : public Animal, public Reptile {

};

int main() {
    Snake snake;
    snake.breathe();

    return 0;
}