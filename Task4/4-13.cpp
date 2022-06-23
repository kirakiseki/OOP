#include <iostream>

using namespace std;

class Elevator {

public:
    static int id;
    int price;

    explicit Elevator(int _price) : price(_price) {
        id++;
    }

};

class pElevator : virtual public Elevator {
public:
    int passenger_load;

    pElevator(int _price, int _passenger) : Elevator(_price), passenger_load(_passenger) { id++; }

    double priceUnit() { return (double) price / passenger_load; }
};

class cElevator : virtual public Elevator {
public:
    int cargo_load;

    cElevator(int _price, int _cargo) : Elevator(_price), cargo_load(_cargo) { id++; }

    double priceUnit() { return (double) price / cargo_load; }
};

class dElevator : public pElevator, public cElevator {
public:
    dElevator(int _price, int _passenger, int _cargo) : Elevator(_price), pElevator(_price, _passenger),
                                                        cElevator(_price, _cargo) { id++; }

};

int Elevator::id = 0;

int main() {
    cout << "Please input dElevator price passenger_load and cargo_load." << endl;
    int price, passenger, cargo;
    cin >> price >> passenger >> cargo;
    dElevator d(price, passenger, cargo);
    cout << "Unit price: price/passenger_load " << d.pElevator::priceUnit() << endl;
    cout << "Unit price: price/cargo_load " << d.cElevator::priceUnit() << endl;
    return 0;
}