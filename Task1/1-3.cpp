#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long int ull;

class Factorial {
public:
    void fact(int _n);

    void showResult() const;

    bool isRight() const;

private:
    int n;
    ull value;
};

void Factorial::fact(int _n) {
    try {
        n = _n;
        if (_n > 20)
            throw invalid_argument("n should not be bigger than 20 in ull range!");
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    value = 1;
    for (int i = n; i > 1; --i) {
        value *= i;
    }
}

void Factorial::showResult() const {
    cout << n << "! = " << value << endl;
}

bool Factorial::isRight() const {
    return value == (ull) tgamma(n + 1);
}

int main() {
    int n;
    Factorial fact{};
    cin >> n;
    fact.fact(n);
    fact.showResult();
    if (fact.isRight()) {
        cout << "Answer is right." << endl;
    } else {
        cout << "Answer is wrong. Should be " << tgamma(n + 1) << endl;
    }
    return 0;
}