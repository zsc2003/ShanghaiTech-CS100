#include <stdlib.h>
#include <stdio.h>

class LivingThing {
public:
    void breathe() {
        printf("I'm breathing as a living thing.\n");
    }
};

class Animal : public LivingThing {
public:
    void breathe() {
        printf("I'm breathing as an animal.\n");
    }
};

class Reptile : public LivingThing {
public:
    void breathe() {
        printf("I'm breathing as a reptile.\n");
    }
};

class Snake : public Animal, public Reptile {
public:
    void breathe() {
        printf("I'm breathing as a snake.\n");
    }
};

int main() {
    Snake snake;
    snake.breathe();

    return 0;
}