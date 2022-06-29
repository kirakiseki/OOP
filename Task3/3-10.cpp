#include <iostream>
#include <type_traits>
#include <stdexcept>

using namespace std;

class Complex {
public:
    Complex(double _a, double _b) : a(_a), b(_b) {}

    template<typename T>
    explicit Complex(T _a);

    Complex operator+(Complex z) const { return {a + z.a, b + z.b}; };

    template<typename T>
    explicit operator T();

    void showValue() const;

private:
    double a, b;
};

void Complex::showValue() const {
    if (a == 0 && b == 0) cout << 0;
    else if (a == 0) cout << b << "i";
    else if (b == 0) cout << a;
    else if (b == 1) cout << a << " + i";
    else if (b == -1) cout << a << " - i";
    else if (b < 0) cout << a << " - " << -b << "i";
    else cout << a << " + " << b << "i";
}

template<typename T>
Complex::Complex(T _a) {
    try {
        if ((!is_same<T, int>::value) &&
            (!is_same<T, short>::value) &&
            (!is_same<T, char>::value) &&
            (!is_same<T, double>::value) &&
            (!is_same<T, float>::value) &&
            (!is_same<T, long>::value))
            throw invalid_argument("illegal type.");
        cout << "convert type T to Complex." << endl;
        a = _a;
        b = 0;
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }
}

template<typename T>
Complex::operator T() {
    try {
        if ((!is_same<T, int>::value) &&
            (!is_same<T, short>::value) &&
            (!is_same<T, char>::value) &&
            (!is_same<T, double>::value) &&
            (!is_same<T, float>::value) &&
            (!is_same<T, long>::value))
            throw invalid_argument("illegal type.");
        cout << "convert Complex to type T." << endl;
        return a;
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
}

int main() {
    int a, b;
    cout << "Please input z1." << endl;
    cin >> a >> b;
    Complex z1(a, b);
    cout << "z1 = ";
    z1.showValue();
    cout << endl << endl;

    Complex z2 = z1 + (Complex) 5;
    cout << "z1 + (Complex) 5 = ";
    z2.showValue();
    cout << endl << endl;

    int z3 = (int) z1 + 5;
    cout << "(int) z1 + 5 = " << z3 << endl << endl;

    double z4 = (double) z1 + 3.14;
    cout << "(double) z1 + 3.14 = " << z4 << endl << endl;

    unsigned int z5 = (unsigned int) z1 + 5;
    cout << "(unsigned int) z1 + 5 = " << z5 << endl;
    return 0;
}