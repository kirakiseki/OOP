#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long int ull;

class Factorial {
public:
    void f(int n);

    void showResult() const;

    bool isRight() const;

private:
    int value;
    ull fact;
};

void Factorial::f(int n) {
    try {
        value = n;
        if (n > 20)
            throw invalid_argument("value should not be bigger than 20 in ull range!");
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    fact = 1;
    for (int i = value; i > 1; --i) {
        fact *= i;
    }
}

void Factorial::showResult() const {
    cout << value << "! = " << fact << endl;
}

bool Factorial::isRight() const {
    return fact == (ull) tgamma(value + 1);
}

int main() {
    int n;
    Factorial fact{};
    cout << "Please input integer n." << endl;
    cin >> n;
    fact.f(n);
    fact.showResult();
    if (fact.isRight()) {
        cout << "Answer is right." << endl;
    } else {
        cout << "Answer is wrong. Should be " << tgamma(n + 1) << endl;
    }
    return 0;
}