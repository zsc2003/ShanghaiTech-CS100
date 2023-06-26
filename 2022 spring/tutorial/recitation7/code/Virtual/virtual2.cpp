#include <iostream>
#include <vector>

using namespace std;

class Vehicle{
public:
    Vehicle(){
        cout << "Constructor of Vehicle" << endl;
    }
    virtual ~Vehicle(){
        cout << "Destructor of vehicle" << endl;
    };
    virtual void display(){
        cout << "I'm a vehicle" << endl;
    }
};

class Bicycle : public Vehicle{
public:
    Bicycle(){
        cout << "Constructor of Bicycle" << endl;
    }
    ~Bicycle(){
        cout << "Destructor of Bicycle" << endl;
    }
    void display() override{
        cout << "I'm a bicycle" << endl;
    }
};

class Tesla : public Vehicle{
public:
    Tesla(){
        cout << "Constructor of Tesla" << endl;
    }
    ~Tesla(){
        cout << "Destructor of Tesla" << endl;
    }
    void display() override{
        cout << "I'm a Tesla" << endl;
    }
};

class MarsRover : public Vehicle{
public:
    MarsRover(){
        cout << "Constructor of Mars Rover" << endl;
    }
    ~MarsRover(){
        cout << "Destructor of Mars Rover" << endl;
    }
    void display() override{
        cout << "I'm a Mars Rover!" << endl;
    }
};


int main(){
    // Deconstrutor call without virtual
    MarsRover marsrover;

    // Usage of virtual destructor
    // Try using non-virtual destructor and see result
    MarsRover *marsrover2 = new MarsRover;
    Vehicle *vehicle = marsrover2;
    delete vehicle;

    // Application of polymorphism
    Bicycle bicycle;
    Tesla tesla;

    vector<Vehicle*> vehicles = {&marsrover, &bicycle, &tesla};

    for(auto v: vehicles){
        v->display();
    }


    return 0;
}
