#include <iostream>

using namespace std;

class Vehicle{
public:
    void display(){
        cout << "I'm vehicle" << endl;
    }
    virtual void display2(){
        cout << "I'm vehicle" << endl;
    }
};

class Bicycle : public Vehicle{
public:
    void display() {
        cout << "I'm bicycle" << endl;
    }
    void display2() override{
        cout << "I'm bicycle" << endl;
    }
};


int main(){
    Bicycle *bike = new Bicycle;
    Vehicle *vehicle = bike;
    bike->display();
    vehicle->display();
    bike->display2();
    vehicle->display2();

    return 0;
}
