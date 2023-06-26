#include <iostream>
#include <vector>

using namespace std;

class Vehicle{
public:
    Vehicle(){
        cout << "Constructor of Vehicle" << endl;
    }
    virtual ~Vehicle(){
        cout << "Deconstructor of vehicle" << endl;
    };
    virtual void display() = 0;
};

class Bicycle : public Vehicle{
public:
    Bicycle(){
        cout << "Constructor of Bicycle" << endl;
    }
    ~Bicycle(){
        cout << "Deconstructor of Bicycle" << endl;
    }
    void display() override{
        cout << "I'm a bicycle" << endl;
    }
};

int main(){
    // Create an instance of abstract class
    // Vehicle v;

    Bicycle b;
    b.display();

    return 0;
}
